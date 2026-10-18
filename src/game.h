#pragma once

#include <SDL2/SDL.h>

class Game {
public:
	Game();
	~Game();

	void Initialize();
	void Destroy();
	void ProcessInput();
	void Setup();
	void Update();
	void Render();
	void Run();

	int windowWidth;
	int windowHeight;

private:
	bool isRunning = false;
	SDL_Window* window;
	SDL_Renderer* renderer;

};