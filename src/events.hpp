#pragma once

#include <SDL2/SDL.h>

#include "SDL2/SDL_keycode.h"
#include "ecs.h"
#include "event.hpp"

class CollisionEvent : public Event {
public:
	Entity a;
	Entity b;

	CollisionEvent(Entity a, Entity b): a(a), b(b) {}
};

class KeyPressEvent : public Event {
public:
	SDL_Keycode symbol;
	
	KeyPressEvent(SDL_Keycode symbol): symbol(symbol) {}
};