#pragma once

#include <SDL2/SDL.h>

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

class RenderSystem : public System {
public:
	RenderSystem() {
		RequireComponent<TransformComponent>();
		RequireComponent<SpriteComponent>();
	}
	~RenderSystem() override = default;

	void Update(double deltaTime) override {}

	void Render(SDL_Renderer* renderer) {
		for (auto entity: GetEntities()) {
			const auto transform = entity.GetComponent<TransformComponent>();
			const auto sprite = entity.GetComponent<SpriteComponent>();

			SDL_Rect dstRect = {
				static_cast<int>(transform.position.x),
				static_cast<int>(transform.position.y),
				static_cast<int>(sprite.width * transform.scale.x),
				static_cast<int>(sprite.height * transform.scale.y)
			};

			SDL_RenderCopyEx(
				renderer, 
				sprite.texture, 
				&sprite.srcRect, 
				&dstRect, 
				transform.rotation, 
				NULL, 
				SDL_FLIP_NONE
			);
		}
	}
};