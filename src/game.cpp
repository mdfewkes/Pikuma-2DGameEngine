#include "game.h"
#include "SDL2/SDL_render.h"
#include "SDL2/SDL_video.h"

#include <iostream>
#include <SDL2/SDL.h>

Game::Game() {

}
Game::~Game() {

}

void Game::Initialize() {
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		std::cerr << "Error initializing SDL." << std::endl;
		return;
	}
	std::cout << "SDL initialized." << std::endl;

	SDL_Window* window = SDL_CreateWindow(
		NULL, 
		SDL_WINDOWPOS_CENTERED, 
		SDL_WINDOWPOS_CENTERED, 
		800,
		600,
		SDL_WINDOW_BORDERLESS);
	if (!window) {
		std::cerr << "Error creating SDL window." << std::endl;
	}

	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
	if (!renderer) {
		std::cerr << "Error creating SDL renderer." << std::endl;
	}
}

void Game::Run() {
	// while(true) {
	// 	ProcessInput();
	// 	Update();
	// 	Render();
	// }
}

void Game::ProcessInput() {
}
void Game::Update() {
}
void Game::Render() {
}

void Game::Destroy() {
}
