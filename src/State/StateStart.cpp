#include "StateStart.h"

#include "StatePlay.h"
#include "StateSelectStage.h"

StateStart::StateStart(Game* game) : StateMenu("Super CLC Bros", game) {
	AddMenuItem(
		[game]() { game->PushState(std::make_unique<StateSelectStage>(game)); }, "Play"
	);
	AddMenuItem([]() {}, "Settings");
	AddMenuItem([game]() { game->window.close(); }, "Exit");
}
