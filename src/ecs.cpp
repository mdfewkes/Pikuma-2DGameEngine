#include "ecs.h"

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
	entities.erase(std::find(entities.begin(), entities.end(), [&entity](Entity other){
		return entity.GetId() == other.GetId();
	}), entities.end());
}
std::vector<Entity> System::GetEntities() const {
	return entities;
}
