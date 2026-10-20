#pragma once

#include <SDL2/SDL.h>

// const int FPS = 60;
// const int MILLISECONDS_PER_FRAME = 1000 / FPS;

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
	int millisecondsPreviousFrame;
	SDL_Window* window;
	SDL_Renderer* renderer;

};