#pragma once

#include "ecs.h"
#include "event.hpp"


class CollisionEvent : public Event {
public:
	CollisionEvent();

	Entity a;
	Entity b;

};