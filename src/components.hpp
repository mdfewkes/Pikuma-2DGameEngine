#pragma once

#include <glm/glm.hpp>

// #include "ecs.h"

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