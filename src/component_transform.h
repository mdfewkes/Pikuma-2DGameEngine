#pragma once

#include <glm/glm.h>

#include "ecs.h"

struct TransformComponent {
	glm::vec2 position;
	glm::vec2 scale;
	double rotation;
};