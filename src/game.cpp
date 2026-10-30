#include "game.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <glm/glm.hpp>

#include "ecs.h"
#include "logger.h"

// #include "component_transform.h"

Game::Game() {
	isRunning = false;
	registry = new Registry();
	Logger::Log("Game constructor called!");
}
Game::~Game() {
	isRunning = false;
	Logger::Log("Game destructor called!");
}

void Game::Initialize() {
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		Logger::Err("Error initializing SDL.");
		return;
	}

	SDL_DisplayMode displayMode;
	SDL_GetCurrentDisplayMode(0, &displayMode);
	windowWidth = 800;//displayMode.w;
	windowHeight = 600;//displayMode.h;
	window = SDL_CreateWindow(
		NULL, 
		SDL_WINDOWPOS_CENTERED, 
		SDL_WINDOWPOS_CENTERED, 
		windowWidth,
		windowHeight,
		SDL_WINDOW_BORDERLESS);
	if (!window) {
		Logger::Err("Error creating SDL window.");
	}
	SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);

	renderer = SDL_CreateRenderer(window, 0, SDL_RENDERER_PRESENTVSYNC);
	if (!renderer) {
		Logger::Err("Error creating SDL renderer.");
	}

	isRunning = true;
}

void Game::Destroy() {
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void Game::ProcessInput() {
	SDL_Event sdlEvent;
	while (SDL_PollEvent(&sdlEvent)) {
		switch (sdlEvent.type) {
		case SDL_QUIT:
			isRunning = false;
			break;
		case SDL_KEYDOWN:
			if (sdlEvent.key.keysym.sym == SDLK_ESCAPE) {
				isRunning = false;
			}
			break;
		}
	}

}

void Game::Setup() {
	Entity tank = registry->CreateEntity();
	// registry->AddComponent<TransformComponent>(tank);
	// registry->AddComponent<BoxCollideromponent>(tank);
	// registry->AddComponent<SpriteComponent>(tank, "./assets/images/tank.png");

	Entity truck = registry->CreateEntity();
	// registry->AddComponent<TransformComponent>(truck);
	// registry->AddComponent<BoxCollideromponent>(truck);
	// registry->AddComponent<SpriteComponent>(truck, "./assets/images/truck.png");
}

void Game::Update() {
	// // Adhear to framerate
	// int timeToWait = MILLISECONDS_PER_FRAME - (SDL_GetTicks() - millisecondsPreviousFrame);
	// if (timeToWait > 0 && timeToWait <= MILLISECONDS_PER_FRAME) {
	// 	SDL_Delay(timeToWait);
	// }

	float deltaTime = (SDL_GetTicks() - millisecondsPreviousFrame) / 1000.0f;
	millisecondsPreviousFrame = SDL_GetTicks();

	// MovementSystem.Update();
	// CollisionSystem.Update();
}

void Game::Render() {
	SDL_SetRenderDrawColor(renderer, 21, 21, 21, 255);
	SDL_RenderClear(renderer);

	// SDL_Surface* surface = IMG_Load("./assets/images/tank-tiger-right.png");
	// SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

	// SDL_Rect dstRect = {
	// 	static_cast<int>(playerPosition.x), 
	// 	static_cast<int>(playerPosition.y), 
	// 	32, 
	// 	32
	// };
	// SDL_RenderCopy(renderer,texture, NULL, &dstRect);

	// SDL_FreeSurface(surface);
	// SDL_DestroyTexture(texture);

	SDL_RenderPresent(renderer);
}

void Game::Run() {
	Setup();
	while(isRunning) {
		ProcessInput();
		Update();
		Render();
	}
}
