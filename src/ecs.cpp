#include "ecs.h"
#include "logger.h"
#include <algorithm>

int IComponent::nextId = 0;

Entity::Entity(int id) : id(id) {}

int Entity::GetId() const {
	return id;
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
	int entityId = numEntities++;
	if (entityId >= entityComponentSignatures.size()) {
		entityComponentSignatures.resize(entityId + 1);
	}
	Entity entity(entityId);
	entitiesToBeAdded.insert(entity);

	Logger::Log("Entity created with id = " + std::to_string(entityId));
	return entity;
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

void Registry::Update() {
	
}