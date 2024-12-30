#include "Game.h"

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <cassert>
#include <iostream>
#include <memory>

#include "Definitions.h"
#include "State/StatePlay.h"
#include "State/StateStart.h"

Game::Game() : window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Super CLC Bros") {
	window.setFramerateLimit(144);

	PushState(std::make_unique<StateStart>(this));

	std::cout << "Game initialized.\n";
}

void Game::Run() {
	sf::Clock clock;
	auto nextTickTime = clock.getElapsedTime().asMicroseconds();
	while (IsOpen()) {
		while (nextTickTime <= clock.getElapsedTime().asMicroseconds()) {
			HandleEvents();
			Update();
			nextTickTime += TIME_PER_TICK;
		}
		double deltaTime =
			static_cast<double>(clock.getElapsedTime().asMicroseconds() - nextTickTime) /
			TIME_PER_TICK;

		window.clear(sf::Color(90, 101, 230));
		Render(deltaTime);
		window.display();
	}
}

void Game::StartGame(std::string mapPath, std::unique_ptr<GameState> gameState) {
	if (dynamic_cast<StatePlay*>(&GetState()))
		PopState();
	if (gameState->GetLives() > 0)
		PushState(std::make_unique<StatePlay>(this, std::move(gameState), mapPath));
}

void Game::Update() {
	GetState().Update();
}
void Game::Render(double deltaTime) {
	GetState().Render(deltaTime);
}
void Game::HandleEvents() {
	for (sf::Event event; window.pollEvent(event);) {
		switch (event.type) {
		case sf::Event::Closed:
			window.close();
			break;
		default:
			GetState().OnSFMLEvent(event);
			break;
		}
	}
}
bool Game::IsOpen() {
	return window.isOpen();
}

State& Game::GetState() {
	assert(states.size() > 0 && "Menu state should be here!");
	return *states.top();
}
void Game::PopState() {
	if (states.size() == 1) {
		// Silently fail to avoid crashing
		std::cerr << "Tried to pop last game state!\n";
		return;
	}
	do {
		GetState().OnExit();
		states.pop();
		GetState().OnEnter();
	} while (states.size() > 1 && GetState().IsIntermediary());
}
void Game::PushState(std::unique_ptr<State> state) {
	if (!states.empty())
		GetState().OnExit();
	states.push(std::move(state));
	GetState().OnEnter();
}
