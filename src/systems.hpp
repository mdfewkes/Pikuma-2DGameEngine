#pragma once

#include <SDL2/SDL.h>

#include "SDL2/SDL_render.h"
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

			SDL_Rect objRect = {
				static_cast<int>(transform.position.x), 
				static_cast<int>(transform.position.y), 
				sprite.width, 
				sprite.height
			};
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			SDL_RenderFillRect(renderer, &objRect);
		}
	}
};