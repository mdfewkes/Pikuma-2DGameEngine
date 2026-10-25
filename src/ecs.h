#pragma once

#include "logger.h"

#include <bitset>
#include <typeindex>
#include <utility>
#include <vector>
#include <unordered_map>
#include <set>

const unsigned int MAX_COMPONENTS = 32;
typedef std::bitset<MAX_COMPONENTS> Signature;

class Entity {
public:
	Entity(int id);
	Entity(const Entity& entity) = default;
	~Entity() = default;

	int GetId() const;

	Entity& operator= (const Entity& other) = default;
	bool operator== (const Entity other) {
		return id == other.GetId();
	}
	bool operator!= (const Entity other) {
		return id != other.GetId();
	}

private:
	int id;

};

struct IComponent {
protected:
	static int nextId;

};

template<typename TComponent>
class Component : public IComponent {
public:
	static int GetId() {
		static auto id = nextId++;
		return id;
	}
	
};

class System {
public:
	System() = default;
	virtual ~System() = default;

	const Signature& GetSignature() const;

	void AddEntity(Entity entity);
	void RemoveEntity(Entity entity);
	std::vector<Entity> GetEntities() const;

	template<typename TComponent> void RequireComponent();

private:
	Signature componentSignature;
	std::vector<Entity> entities;
	
};

class IPool {
public:
	virtual ~IPool() {}
};

template <typename T>
class Pool : public IPool {
public:
	Pool(int size = 100) { Resize(size); }
	~Pool() = default;

	bool IsEmpty() const { return data.empty(); }
	int GetSize() const { return data.size(); }
	void Resize(int n) { data.Resize(); }
	void Clear() { data.clear(); }
	void Add(T object) { data.push_back(object); }
	void Set(int index, T object) { data[index] = object; }
	T& Get(int index) { return static_cast<T&>(data[index]); }

	T& operator[] (unsigned int index) { return data[index]; }

private:
	std::vector<T> data;
};

class Registry {
public:
	Registry() = default;

	void Update();

	Entity CreateEntity();
	// void DistroyEntity(Entity entity);

	template<typename TComponent, typename ...TArgs> void AddComponent(Entity entity, TArgs&& ...args);
	// template<typename TComponent> void RemoveComponent(Entity entity);
	// template<typename TComponent> boolHasComponent(Entity entity);
	// template<typename TComponent> Component GetComponent(Entity entity);

	// void AddSystem();
	// void RemoveSystem();
	// boolHasSystem();
	// System GetSystem();

	// void AddEntityToSystem(Entity entity);


private:
	int numEntities = 0;
	std::vector<IPool*> componentPools;
	std::vector<Signature> entityComponentSignatures;
	std::unordered_map<std::type_index, System*> systems;
	std::set<Entity> entitiesToBeAdded;
	std::set<Entity> entitiesToBeRemoved;
	
};





template<typename TComponent>
void System::RequireComponent() {
	const auto componentId = Component<TComponent>::GetId();
	componentSignature.set(componentId);
}



template<typename TComponent, typename ...TArgs> 
void Registry::AddComponent(Entity entity, TArgs&& ...args) {
	const auto componentId = Component<TComponent>::GetId();
	const auto entityId = entity.GetId();

	if (componentId >= componentPools.size()) {
		componentPools.resize(componentId + 1, nullptr);
	}

	if (!componentPools[componentId]) {
		Pool<TComponent>* newComponentPool = new Pool<TComponent>();
		componentPools[componentId] = newComponentPool;
	}

	Pool<TComponent> componentPool = Pool<TComponent>(componentPools[componentId]);

	if (entityId >= componentPool.GetSize()) {
		componentPool->Resize(numEntities);
	}

	TComponent newComponent(std::forward<TArgs>(args)...);

	componentPool->Set(entityId, newComponent);

	entityComponentSignatures[entityId].set(componentId);
}