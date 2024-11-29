#ifndef _STATEMENU_H
#define _STATEMENU_H

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include <vector>
#include <functional>
#include "../Game.h"
#include "State.h"

class StateMenu : public State {
protected:
    Game* game;
    sf::Font font;
    sf::Text titleText;

    struct MenuItem {
		std::function<void()> action;
		sf::Text text;
    };

    std::vector<MenuItem> items;           
	size_t selectedItem = 0;
	void AddMenuItem(std::function<void()> action, sf::Text text);

public:
    StateMenu(Game* game);

    virtual void OnEnter() override;
    virtual void Update() override;
    virtual void Render(double deltaTime) override;
    virtual void OnSFMLEvent(const sf::Event& event) override;
};


#endif 