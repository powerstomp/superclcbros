#ifndef STATEMENU_H
#define STATEMENU_H

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
        std::string label;          
        bool* configValue;           
        sf::Text text;               
    };

    std::vector<MenuItem> items;     
    size_t selectedIndex = 0;       

    void UpdateOption();

public:
    StateMenu(Game* game);

    virtual void OnEnter() override;
    virtual void Update() override;
    virtual void Render(double deltaTime) override;
    virtual void OnSFMLEvent(const sf::Event& event) override;

    void AddMenuItem(const std::string& label, bool* configValue);
};

#endif 
