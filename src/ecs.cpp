#include "ecs.h"

Entity::Entity(int id) : id(id) {}

int Entity::GetId() const {
	return id;
}



const Signature& System::GetSignature() const {
	return componentSignature;
}

void System::AddEntity(Entity entity) {

}
void System::RemoveEntity(Entity entity) {

}
std::vector<Entity> System::GetEntities() const {
	return entities;
}
