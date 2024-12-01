#include "StateMenu.h"

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Keyboard.hpp>

#include "../Utility/ServiceLocator.h"
#include "StatePlay.h"

StateMenu::StateMenu(Game* game) : game{game}, font{ServiceLocator<sf::Font>::Get()} {
	titleText.setFont(font);
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

void StateMenu::UpdateItemDisplay() {
	for (std::size_t i = 0; i < items.size(); i++) {
		if (i == selectedItem) {
			items[i].text.setFillColor(sf::Color::Yellow);
			items[i].text.setScale(1.2f, 1.2f);
		} else {
			items[i].text.setFillColor(sf::Color::White);
			items[i].text.setScale(1.0f, 1.0f);
		}
	}
}

void StateMenu::Render(double deltaTime) {
	game->window.draw(titleText);

	for (auto& item : items)
		game->window.draw(item.text);
}

void StateMenu::OnSFMLEvent(const sf::Event& event) {
	if (event.type == event.KeyPressed) {
		if (event.key.code == sf::Keyboard::Key::Up) {
			selectedItem = (selectedItem == 0) ? items.size() - 1 : selectedItem - 1;
			UpdateItemDisplay();
		} else if (event.key.code == sf::Keyboard::Key::Down) {
			selectedItem = (selectedItem == items.size() - 1) ? 0 : selectedItem + 1;
			UpdateItemDisplay();
		} else if (event.key.code == sf::Keyboard::Key::Enter && items.size() > 0) {
			auto& item = items[selectedItem];
			item.onPress();
			item.updateDisplay(item.text);
		}
	}
}

void StateMenu::AddMenuItem(
	std::function<void()> onPress, std::function<void(sf::Text&)> updateDisplay
) {
	MenuItem menuItem{.onPress = onPress, .updateDisplay = updateDisplay};

	menuItem.text.setFont(font);

	float yOffset = 200.0f + items.size() * 50.0f;
	auto viewSize = game->window.getDefaultView().getSize();
	menuItem.text.setPosition(
		viewSize.x / 2 - titleText.getGlobalBounds().width / 2, yOffset
	);

	menuItem.updateDisplay(menuItem.text);
	items.push_back(std::move(menuItem));
}
void StateMenu::AddMenuItem(std::function<void()> onPress, const std::string& text) {
	AddMenuItem(onPress, [text](sf::Text& sfmlText) mutable {
		sfmlText.setString(text);
	});
}

void StateMenu::AddMenuItem(bool& value, const std::string& _text) {
	AddMenuItem(
		[&value]() mutable { value = !value; },
		[text = std::string(_text), &value](sf::Text& sfmlText) {
			sfmlText.setString(text + (value ? " (On)" : "(Off)"));
		}
	);
}
