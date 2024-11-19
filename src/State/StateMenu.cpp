#include "StateMenu.h"

#include <SFML/Graphics/Font.hpp>
#include <SFML/System/Vector2.hpp>

#include "../Utility/ServiceLocator.h"

StateMenu::StateMenu(Game* game) : game{game}, mario{Mario(sf::Vector2f(200, 0))} {
	titleText.setFont(ServiceLocator<sf::Font>::Get());
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
	mario.Update();
}

void StateMenu::Render(double deltaTime) {
	game->window.draw(titleText);
	game->window.draw(*mario.GetSprite());
}
void StateMenu::OnSFMLEvent(const sf::Event& event) {
	// if (event.type == event.KeyPressed)
	// game->PushState(std::make_unique<StatePlay>(game));
}
