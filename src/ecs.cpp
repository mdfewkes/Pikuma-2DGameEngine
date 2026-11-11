#include "ecs.h"

#include <algorithm>

int IComponent::nextId = 0;

Entity::Entity(int id) : id(id) {}

int Entity::GetId() const {
	return id;
}

void Entity::Destroy() {
	Logger::Log("  Destroy {");
	registry->DestroyEntity(*this);
	Logger::Log("  Destroy }");
}


const Signature& System::GetSignature() const {
	return componentSignature;
}

void System::AddEntity(Entity entity) {
	entities.push_back(entity);
}
void System::RemoveEntity(Entity entity) {
	entities.erase(std::remove_if(entities.begin(), entities.end(), [&entity](Entity other){
		return entity == other;
	}), entities.end());
}
std::vector<Entity> System::GetEntities() const {
	return entities;
}




Entity Registry::CreateEntity() {
	int entityId;
	if (freeIds.empty()) {
		entityId = numEntities++;
		if (entityId >= entityComponentSignatures.size()) {
			entityComponentSignatures.resize(entityId + 1);
		}
	} else {
		entityId = freeIds.front();
		freeIds.pop_front();
	}

	Entity entity(entityId);
	entity.registry = this;
	entitiesToBeAdded.insert(entity);

	Logger::Log("Entity created with id = " + std::to_string(entityId));
	return entity;
}
void Registry::DestroyEntity(Entity entity) {
	entitiesToBeRemoved.insert(entity);
    Logger::Log("Entity " + std::to_string(entity.GetId()) + " was killed");
}

void Registry::AddEntityToSystem(Entity entity) {
	const auto entityId = entity.GetId();
	const auto& entityComponentSigniture = entityComponentSignatures[entityId];

	for (auto&system: systems) {
		const auto& systemComponentSigniture = system.second->GetSignature();

		bool isInterested = (entityComponentSigniture & systemComponentSigniture) == systemComponentSigniture;
		if (isInterested) {
			system.second->AddEntity(entity);
		}
	}
}
void Registry::RemoveEntityFromSystem(Entity entity) {
	const auto entityId = entity.GetId();

	for (auto system: systems) {
		system.second->RemoveEntity(entity);
	}

	entityComponentSignatures[entityId].reset();

	freeIds.push_back(entityId);
}

void Registry::SubscribeToEvents(EventBus* eventBus) {
	for (auto& system: systems) {
		system.second->SubscribeToEvents(eventBus);
	}
}

void Registry::Update(double deltaTime, EventBus* eventBus) {
	for (auto& system: systems) {
		system.second->Update(deltaTime, eventBus);
	}

	for (auto entity: entitiesToBeAdded) {
		AddEntityToSystem(entity);
	}
	entitiesToBeAdded.clear();

	for (auto entity: entitiesToBeRemoved) {
		RemoveEntityFromSystem(entity);
	}
	entitiesToBeRemoved.clear();
}

void Registry::Render(SDL_Renderer* renderer) {
	for (auto& system: systems) {
		system.second->Render(renderer);
	}
}