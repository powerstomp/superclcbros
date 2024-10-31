#include "StateMenu.h"

#include <SFML/Graphics/Font.hpp>
#include <iostream>

StateMenu::StateMenu(Game* game) : game{game} {
	titleText.setFont(game->GetFont());
	titleText.setString("Super CLC Bros");
	titleText.setCharacterSize(50);
	titleText.setFillColor(sf::Color::White);

	auto viewSize = game->window.getDefaultView().getSize();
	titleText.setPosition(viewSize.x / 2 - titleText.getGlobalBounds().width / 2, 50);
}

void StateMenu::OnEnter() {
	game->window.setView(game->window.getDefaultView());
}
void StateMenu::Update() {
}

void StateMenu::Render(double deltaTime) {
	game->window.draw(titleText);
}
void StateMenu::OnSFMLEvent(const sf::Event& event) {
	// if (event.type == event.KeyPressed)
	// game->PushState(std::make_unique<StatePlay>(game));
}
