#pragma once

#include "SDL2/SDL_rect.h"
#include "SDL2/SDL_render.h"
#include "SDL2/SDL_timer.h"
#include <glm/glm.hpp>

struct TransformComponent {
	glm::vec2 position;
	glm::vec2 scale;
	double rotation;

	TransformComponent(glm::vec2 position = glm::vec2(0.0f,0.0f), glm::vec2 scale = glm::vec2(1.0f,1.0f), double rotation = 0.0) {
		this->position = position;
		this->scale = scale;
		this->rotation = rotation;
	}
};

struct RigidbobyComponent {
	glm::vec2 velocity;

	RigidbobyComponent(glm::vec2 velocity = glm::vec2(0,0)) {
		this->velocity = velocity;
	}
};

struct SpriteComponent {
	SDL_Texture* texture;
	int width, height;
	SDL_Rect srcRect;
	int zIndex = 0;

	SpriteComponent(SDL_Texture* texture = nullptr, int zIndex = 0, int width = 0, int height = 0, int srcRectX = 0, int srcRectY = 0) {
		this->texture = texture;
		this->width = width;
		this->height = height;
		this->zIndex = zIndex;

		if (width == 0 && height == 0) {
			SDL_QueryTexture(texture, NULL, NULL, &this->width, &this->height);
		}

		this->srcRect = {srcRectX, srcRectY, this->width, this->height};
	}
};

struct AnimationComponent {
	int numFrames;
	int currentFrame;
	int frameRate;
	bool looping;
	int startTime;

	AnimationComponent(int numFrames = 1, int frameRate = 1, bool looping = true) {
		this->numFrames = numFrames;
		this->currentFrame = 1;
		this->frameRate = frameRate;
		this->looping = looping;
		this->startTime = SDL_GetTicks();
	}
};