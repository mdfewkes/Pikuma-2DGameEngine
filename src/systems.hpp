#pragma once

#include "ecs.h"
#include "components.hpp"

class MovementSystem : public System {
public:
	MovementSystem() {
		RequireComponent<TransformComponent>();
		RequireComponent<RigidbobyComponent>();
	}
	~MovementSystem() override = default;

	void Update(double deltaTime) override {
		for (auto entity: GetEntities()) {
			auto& transform = entity.GetComponent<TransformComponent>();
			const auto rigidbody = entity.GetComponent<RigidbobyComponent>();

			transform.position.x += rigidbody.velocity.x * deltaTime;
			transform.position.y += rigidbody.velocity.y * deltaTime;
		}
	}

};