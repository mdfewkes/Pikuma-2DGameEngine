#pragma once

#include "ecs.h"
#include "eventbus.h"


class CollisionEvent : public Event {
public:
	CollisionEvent();

	Entity a;
	Entity b;

};