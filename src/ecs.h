#pragma once

#include <bitset>
#include <memory>
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
	bool operator< (const Entity& other) const {
		return id < other.id;
	}
	bool operator> (const Entity& other) const {
		return id > other.id;
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
	Pool(int size = 100) { data.resize(size); }
	virtual ~Pool() = default;

	bool isEmpty() const { return data.empty(); }
	int GetSize() const { return data.size(); }
	void Resize(int n) { data.resize(n); }
	void Clear() { data.clear(); }
	void Add(T object) { data.push_back(object); }
	void Set(int index, T object) { data[index] = object; }
	T& Get(int index) { return static_cast<T&>(data[index]); }

	T& operator [](unsigned int index) { return data[index]; }

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
	template<typename TComponent> void RemoveComponent(Entity entity);
	template<typename TComponent> bool HasComponent(Entity entity) const;
	// template<typename TComponent> TComponent& GetComponent(Entity entity) const;

	template<typename TSystem, typename ...TArgs> void AddSystem(TArgs&& ...args);
	template<typename TSystem> void RemoveSystem();
	template<typename TSystem> bool HasSystem() const;
	template<typename TSystem> TSystem& GetSystem();


private:
	int numEntities = 0;
	std::vector< std::shared_ptr<IPool>> componentPools;
	std::vector<Signature> entityComponentSignatures;
	std::unordered_map<std::type_index, std::shared_ptr<System>> systems;
	std::set<Entity> entitiesToBeAdded;
	std::set<Entity> entitiesToBeRemoved;

	void AddEntityToSystem(Entity entity);
	
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
		std::shared_ptr<Pool<TComponent>> newComponentPool = std::make_shared<Pool<TComponent>>();
		componentPools[componentId] = newComponentPool;
	}

	std::shared_ptr<Pool<TComponent>> componentPool = std::static_pointer_cast<componentPools[componentId]>();

	if (entityId >= componentPool->GetSize()) {
		componentPool->Resize(numEntities);
	}

	TComponent newComponent(std::forward<TArgs>(args)...);

	componentPool->Set(entityId, newComponent);

	entityComponentSignatures[entityId].set(componentId);
}

template<typename TComponent> 
void Registry::RemoveComponent(Entity entity) {
	const auto componentId = Component<TComponent>::GetId();
	const auto entityId = entity.GetId();

	entityComponentSignatures[entityId].set(componentId, false);
}

template<typename TComponent> 
bool Registry::HasComponent(Entity entity) const {
	const auto componentId = Component<TComponent>::GetId();
	const auto entityId = entity.GetId();

	return entityComponentSignatures[entityId].test(componentId);
}

// template<typename TComponent> 
// TComponent& Registry::GetComponent(Entity entity) const {
// 	const auto componentId = Component<TComponent>::GetId();
// 	const auto entityId = entity.GetId();

// 	return componentPools[componentId][entityId];
// }



template<typename TSystem, typename ...TArgs>
void Registry::AddSystem(TArgs&& ...args) {
	std::shared_ptr<TSystem> newSystem = std::make_shared<TSystem>(std::forward<TArgs>(args)...);
	systems.insert(std::make_pair(std::type_index(typeid(TSystem)), newSystem));
}

template<typename TSystem>
void Registry::RemoveSystem() {
	auto system = systems.find(std::type_index(typeid(TSystem)));
	systems.erase(system);
}

template<typename TSystem>
bool Registry::HasSystem() const {
	return systems.find(std::type_index(typeid(TSystem)))!= systems.end();
}

template<typename TSystem>
TSystem& Registry::GetSystem() {
	auto system = systems.find(std::type_index(typeid(TSystem)));
	return *(std::static_pointer_cast<TSystem>(system->second));
}