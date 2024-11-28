#include "StateMenu.h"

#include <SFML/Graphics/Font.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Keyboard.hpp>

#include "../Utility/ServiceLocator.h"
#include "StatePlay.h"

// StateMenu::StateMenu(Game* game) : game{game} {
// 	titleText.setFont(ServiceLocator<sf::Font>::Get());
// 	titleText.setString("Super CLC Bros");
// 	titleText.setCharacterSize(50);
// 	titleText.setFillColor(sf::Color::White);

// 	auto viewSize = game->window.getDefaultView().getSize();
// 	titleText.setPosition(viewSize.x / 2 - titleText.getGlobalBounds().width / 2, 50);
// }

// void StateMenu::OnEnter() {
// 	game->window.setView(game->window.getDefaultView());
// }
// void StateMenu::Update() {
// }

// void StateMenu::Render(double deltaTime) {
// 	game->window.draw(titleText);
// }
// void StateMenu::OnSFMLEvent(const sf::Event& event) {
// 	if (event.type == event.KeyPressed)
// 		if (event.key.code == sf::Keyboard::Key::Enter)
// 			game->PushState(std::make_unique<StatePlay>(game));
// }

StateMenu::StateMenu(Game* game) : game{game}
{}

void StateMenu::OnEnter() {
    // Load font
    font = ServiceLocator<sf::Font>::Get();

    // Initialize title text
    titleText.setFont(font);
    titleText.setString("Super CLC Bros");
    titleText.setCharacterSize(50);
    titleText.setFillColor(sf::Color::White);
    auto viewSize = game->window.getDefaultView().getSize();
    titleText.setPosition(viewSize.x / 2 - titleText.getGlobalBounds().width / 2, 50);
	UpdateOption();
}

void StateMenu::AddMenuItem(const std::string& label, bool* configValue) {
	MenuItem item;
	item.label = label;
	item.configValue = configValue;
	item.text.setFont(font);
	item.text.setString(label);
	item.text.setCharacterSize(30);
	item.text.setFillColor(sf::Color::White);
	items.push_back(item);
}

void StateMenu::UpdateOption(){
    float startY = 150.0f;
    auto viewSize = game->window.getDefaultView().getSize();

    for (size_t i = 0; i < items.size(); ++i) {
        auto& item = items[i];
        item.text.setString(item.label + " [" + (*item.configValue ? "On" : "Off") + "]");
        item.text.setFillColor(i == selectedIndex ? sf::Color::Yellow : sf::Color::White);
        item.text.setPosition(viewSize.x / 2 - item.text.getGlobalBounds().width / 2, startY + i * 40.0f);
    }
}

void StateMenu::Update() {
}

void StateMenu::Render(double deltaTime) {
	game->window.clear(sf::Color::Black);
	game->window.draw(titleText);
	for (const auto& item : items) {
		game->window.draw(item.text);
	}
}

void StateMenu::OnSFMLEvent(const sf::Event& event) {
	if (event.type == sf::Event::KeyPressed) {
		if (event.key.code == sf::Keyboard::Key::Up) {
			if (selectedIndex > 0) {
				--selectedIndex;
			}
		}
		else if (event.key.code == sf::Keyboard::Key::Down) {
			if (selectedIndex < items.size() - 1) {
				++selectedIndex;
			}
		}
		else if (event.key.code == sf::Keyboard::Key::Enter) {
			if (selectedIndex < items.size()) {
				*items[selectedIndex].configValue = !*items[selectedIndex].configValue;
			}
		}
		UpdateOption();
	}
}

