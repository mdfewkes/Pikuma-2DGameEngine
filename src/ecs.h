#pragma once

#include <bitset>
#include <vector>

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

class Registry {
	
};





template<typename TComponent>
void System::RequireComponent() {
	const auto componentId = Component<TComponent>::GetId();
	componentSignature.set(componentId);
}