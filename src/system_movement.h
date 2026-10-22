#pragma once

#include "ecs.h"

class MovementSystem : public System {
public:
	MovementSystem();
	~MovementSystem();

	void Update() {
		for (auto entity: GetEntities()) {
			
		}
	}

};