#include "StateMenu.h"

#include <SFML/Graphics/Font.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Keyboard.hpp>

#include "../Utility/ServiceLocator.h"
#include "StatePlay.h"

StateMenu::StateMenu(Game* game) : game{game} {
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
}

void StateMenu::Render(double deltaTime) {
	game->window.draw(titleText);
}
void StateMenu::OnSFMLEvent(const sf::Event& event) {
	if (event.type == event.KeyPressed)
		if (event.key.code == sf::Keyboard::Key::Enter)
			game->PushState(std::make_unique<StatePlay>(game));
}
