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
public:
	int GetId() const;

private:
	int id;
	
};

class System {
public:
	System() = default;
	virtual ~System() = default;

	const Signature& GetSignature() const;

	void AddEntity(Entity entity);
	void RemoveEntity(Entity entity);
	std::vector<Entity> GetEntities() const;

	template<typename T> void RequireComponent();

private:
	Signature componentSignature;
	std::vector<Entity> entities;
	
};

class Registry {
	
};