#include "StateStart.h"

#include "../Utility/ServiceLocator.h"
#include "StatePlay.h"

StateStart::StateStart(Game* game) : StateMenu(game) {
	sf::Font& font = ServiceLocator<sf::Font>::Get();

	AddMenuItem(
		[game]() { game->PushState(std::make_unique<StatePlay>(game)); },
		sf::Text("Play", font, 30)
	);
	AddMenuItem([]() {}, sf::Text("Settings", font, 30));
	AddMenuItem([game]() { game->window.close(); }, sf::Text("Exit", font, 30));
}
