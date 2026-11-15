#pragma once

#include <SDL2/SDL.h>

#include "ecs.h"
#include "assetstore.h"
#include "eventbus.hpp"

// const int FPS = 60;
// const int MILLISECONDS_PER_FRAME = 1000 / FPS;

class Game {
public:
	Game();
	~Game();

	void Initialize();
	void Destroy();
	void Run();

	static int windowWidth;
	static int windowHeight;
	static int mapWidth;
	static int mapHeight;

private:
	bool isRunning = false;
	bool isDebug = false;
	int millisecondsPreviousFrame;
	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Rect camera;

	Registry registry;
	AssetStore assetStore;
	EventBus eventBus;

	void ProcessInput();
	void Setup();
	void Update();
	void Render();

	void LoadLevel(int level);
};