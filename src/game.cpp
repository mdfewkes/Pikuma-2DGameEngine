#include "game.h"



Game::Game() {

}
Game::~Game() {

}

void Game::Initialize() {

}
void Game::Run() {

}
void Game::ProcessInput() {

}
void Game::Update() {
	while(true) {
		ProcessInput();
		Update();
		Render();
	}
}
void Game::Render() {

}
void Game::Destroy() {

}
