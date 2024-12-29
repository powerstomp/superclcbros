#ifndef _GAME_H
#define _GAME_H

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/Window/Window.hpp>
#include <memory>
#include <stack>

#include "GameState.h"
#include "State/State.h"

class Game {
private:
	std::stack<std::unique_ptr<State>> states;

	void Update();
	void Render(double deltaTime);
	void HandleEvents();

public:
	sf::RenderWindow window;

	Game();

	void Run();
	bool IsOpen();

	void StartGame(std::string mapPath, std::unique_ptr<GameState> gameState);

	State& GetState();
	void PopState();
	void PushState(std::unique_ptr<State>);
};

#endif
