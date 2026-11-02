#include "game.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <glm/glm.hpp>

#include "logger.h"
#include "components.hpp"
#include "systems.hpp"

Game::Game() {
	isRunning = false;
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
	registry.AddSystem<MovementSystem>();
	registry.AddSystem<RenderSystem>();

	assetStore.AddTexture(renderer, "tank-image", "./assets/images/tank-tiger-right.png");
	assetStore.AddTexture(renderer, "truck-image", "./assets/images/truck-ford-right.png");

	Entity tank = registry.CreateEntity();
	tank.AddComponent<TransformComponent>(glm::vec2(10.0f, 30.0f));
	tank.AddComponent<RigidbobyComponent>(glm::vec2(40.0f, 10.0f));
	// tank.AddComponent<BoxCollideromponent>();
	tank.AddComponent<SpriteComponent>(assetStore.GetTexture("tank-image"));

	Entity truck = registry.CreateEntity();
	truck.AddComponent<TransformComponent>(glm::vec2(100.0f, 300.0f));
	// truck.AddComponent<BoxCollideromponent>();
	truck.AddComponent<SpriteComponent>(assetStore.GetTexture("truck-image"));
}

void Game::Update() {
	// // Adhear to framerate
	// int timeToWait = MILLISECONDS_PER_FRAME - (SDL_GetTicks() - millisecondsPreviousFrame);
	// if (timeToWait > 0 && timeToWait <= MILLISECONDS_PER_FRAME) {
	// 	SDL_Delay(timeToWait);
	// }

	float deltaTime = (SDL_GetTicks() - millisecondsPreviousFrame) / 1000.0f;
	millisecondsPreviousFrame = SDL_GetTicks();

	registry.Update(deltaTime);
}

void Game::Render() {
	SDL_SetRenderDrawColor(renderer, 21, 21, 21, 255);
	SDL_RenderClear(renderer);

	registry.GetSystem<RenderSystem>().Render(renderer);

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
