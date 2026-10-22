#pragma once

#include <bitset>
#include <vector>

const unsigned int MAX_COMPONENTS = 32;
typedef std::bitset<MAX_COMPONENTS> Signature;

class Entity {
public:
	Entity(int id);
	~Entity() = default;

	int GetId() const;

private:
	int id;

};

class Component {
	
};

class System {
public:
	System() = default;
	~System() = default;
	
	Signature& GetSignature() const;

	void AddEntity(Entity entity);
	void RemoveEntity(Entity entity);
	std::vector<Entity> GetEntities() const;

private:
	Signature componentSignature;
	std::vector<Entity> entities;
	
};

class Registry {
	
};