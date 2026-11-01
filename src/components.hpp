#pragma once

#include "SDL2/SDL_render.h"
#include <glm/glm.hpp>
#include <string>

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

	SpriteComponent(SDL_Texture* texture = nullptr, int width = 0, int height = 0) {
		this->texture = texture;
		this->width = width;
		this->height = height;

		if (width == 0 && height == 0) {
			SDL_QueryTexture(texture, NULL, NULL, &this->width, &this->height);
		}
	}
};