#include "ecs.h"

Entity::Entity(int id) : id(id) {}

int Entity::GetId() const {
	return id;
}



Signature& System::GetSignature() const {
	
}

void System::AddEntity(Entity entity) {

}
void System::RemoveEntity(Entity entity) {

}
std::vector<Entity> System::GetEntities() const {

}