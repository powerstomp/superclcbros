#include "StateSelectStage.h"

#include "StateSelectPlayer.h"

void StateSelectStage::AddStage(const std::string name, const std::string& mapPath) {
	AddMenuItem(
		[=]() { game->PushState(std::make_unique<StateSelectPlayer>(game, mapPath)); },
		name
	);
}

StateSelectStage::StateSelectStage(Game* game) : StateMenu("Select stage", game) {
	AddStage("Stage A", "assets/A");
	AddStage("Stage B", "assets/B");
	AddStage("Stage C", "assets/C");
}

bool StateSelectStage::IsIntermediary() const {
	return true;
}
