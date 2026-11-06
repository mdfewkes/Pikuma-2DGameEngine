#pragma once

#include <SDL2/SDL.h>
#include <algorithm>
#include <vector>

#include "SDL2/SDL_timer.h"
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
		struct RenderableEntity {
			TransformComponent transformComponent;
			SpriteComponent spriteComponent;
		};
		std::vector<RenderableEntity> renderableEntities;
		for (auto entity: GetEntities()) {
			RenderableEntity renderableEntity;
			renderableEntity.transformComponent = entity.GetComponent<TransformComponent>();
			renderableEntity.spriteComponent = entity.GetComponent<SpriteComponent>();

			renderableEntities.push_back(renderableEntity);
		}
		std::sort(renderableEntities.begin(), renderableEntities.end(), [](const RenderableEntity entityA, const RenderableEntity entityB){
			return entityA.spriteComponent.zIndex < entityB.spriteComponent.zIndex;
		});

		for (auto entity: renderableEntities) {
			const auto transform = entity.transformComponent;
			const auto sprite = entity.spriteComponent;

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

class AnimationSystem : public System {
public:
	AnimationSystem() {
		RequireComponent<SpriteComponent>();
		RequireComponent<AnimationComponent>();
	}
	~AnimationSystem() override = default;

	void Update(double deltaTime) override {
		for (auto entity: GetEntities()) {
			auto& sprite = entity.GetComponent<SpriteComponent>();
			auto& animation = entity.GetComponent<AnimationComponent>();

			animation.currentFrame = ((SDL_GetTicks() - animation.startTime) * animation.frameRate / 1000) % animation.numFrames;
			sprite.srcRect.x = animation.currentFrame * sprite.width;
		}
	}
};

class CollisionSystem : public System {
public:
	CollisionSystem() {
		RequireComponent<BoxCollideComponent>();
	}
	~CollisionSystem() override = default;

	void Update(double deltaTime) override {
		
	}
};

