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

	for(size_t i = 0; i < items.size(); i++) {
		items[i].text.setFillColor((i == selectedItem) ? sf::Color::Red : sf::Color::White);
		items[i].text.setPosition(100, 200 + i * 50);
		game->window.draw(items[i].text);
	}
}
void StateMenu::OnSFMLEvent(const sf::Event& event) {
	if (event.type == event.KeyPressed)
		if (event.key.code == sf::Keyboard::Key::Enter)
			game->PushState(std::make_unique<StatePlay>(game));
		else if(event.key.code == sf::Keyboard::Key::Up)
			selectedItem = (selectedItem == 0) ? items.size() - 1 : selectedItem - 1;
		else if(event.key.code == sf::Keyboard::Key::Down)
			selectedItem = (selectedItem == items.size() - 1) ? 0 : selectedItem + 1;
		else if(event.key.code == sf::Keyboard::Key::Space && items.size() > 0)
			items[selectedItem].action();
		
}



void StateMenu::AddMenuItem(std::function<void()> action, sf::Text text) {
	items.push_back({action, text});
}


	

