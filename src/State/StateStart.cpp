#include "StateStart.h"

#include "StatePlay.h"
#include "StateSelectStage.h"
#include "StateSettings.h"

StateStart::StateStart(Game* game) : StateMenu("Super CLC Bros", game) {
	AddMenuItem(
		[game]() { game->PushState(std::make_unique<StateSelectStage>(game)); }, "Play"
	);
	AddMenuItem(
		[game]() { game->PushState(std::make_unique<StateSettings>(game)); }, "Settings"
	);
	AddMenuItem([game]() { game->window.close(); }, "Exit");
}
