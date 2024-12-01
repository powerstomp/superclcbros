#include "StateStart.h"

#include "../Utility/ServiceLocator.h"
#include "StatePlay.h"

StateStart::StateStart(Game* game) : StateMenu(game) {
	sf::Font& font = ServiceLocator<sf::Font>::Get();

	static bool lulz = false;

	AddMenuItem([game]() { game->PushState(std::make_unique<StatePlay>(game)); }, "Play");
	AddMenuItem([]() {}, "Settings");
	AddMenuItem([game]() { game->window.close(); }, "Exit");
	AddMenuItem(lulz, "LOLING OUT LOUD");
}
