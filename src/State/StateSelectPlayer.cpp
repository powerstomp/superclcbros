#include "StateSelectPlayer.h"

#include "StatePlay.h"

void StateSelectPlayer::AddPlayerType(const std::string name, PlayerType playerType) {
	AddMenuItem(
		[=]() { game->StartGame(mapPath, std::make_unique<GameState>(playerType)); }, name
	);
}

StateSelectPlayer::StateSelectPlayer(Game* game, const std::string& mapPath)
	: StateMenu("Select player type", game), mapPath(mapPath) {
	AddPlayerType("Mario", PlayerType::MARIO);
	AddPlayerType("Luigi", PlayerType::LUIGI);
}
