#include "StateStart.h"
#include "../Utility/ServiceLocator.h"

StateStart::StateStart(Game* game) : StateMenu(game) {}

void StateStart::OnEnter() {
    sf::Font& font = ServiceLocator<sf::Font>::Get();

    sf::Text ContinueText("CONTINUE", font, 30);
    AddMenuItem([this]
    {
        // Load game from file

    }, ContinueText);

    sf::Text NewGameText("NEW GAME", font, 30);
    AddMenuItem([this]
    {
        // Start new game

    }, NewGameText);

    sf::Text SettingsText("SETTING", font, 30);
    AddMenuItem([this]
    {
        // Open settings

    }, SettingsText);

    sf::Text ExitText("EXIT", font, 30);
    AddMenuItem([this]
    {
        game->window.close();
    }, ExitText);

    
}