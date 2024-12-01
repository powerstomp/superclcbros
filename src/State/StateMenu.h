#ifndef _STATEMENU_H
#define _STATEMENU_H

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include <functional>
#include <vector>

#include "../Game.h"
#include "State.h"

class StateMenu : public State {
protected:
	Game* game;
	sf::Font& font;
	sf::Text titleText;

	struct MenuItem {
		std::function<void()> onPress;
		std::function<void(sf::Text&)> updateDisplay;
		sf::Text text;
	};

	std::vector<MenuItem> items;
	std::size_t selectedItem = 0;

	void UpdateItemDisplay();
	void AddMenuItem(
		std::function<void()> onPress, std::function<void(sf::Text&)> updateDisplay
	);
	void AddMenuItem(std::function<void()> onPress, const std::string& text);
	void AddMenuItem(bool& value, const std::string& text);

public:
	StateMenu(Game* game);

	virtual void OnEnter() override;
	virtual void Update() override;
	virtual void Render(double deltaTime) override;
	virtual void OnSFMLEvent(const sf::Event& event) override;
};

#endif
