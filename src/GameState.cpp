#include "GameState.h"

#include <algorithm>
#include <iostream>

GameState::GameState(PlayerType playerType) : playerType(playerType) {
}

int GameState::GetScore() const {
	return score;
}

int GameState::GetLives() const {
	return lives;
}

int GameState::GetTimeRemaining() const {
	return 400 - clock.getElapsedTime().asSeconds();
}

PlayerType GameState::GetPlayerType() const {
	return playerType;
}

void GameState::CollectScore() {
	int curTime = clock.getElapsedTime().asMilliseconds();
	if (curTime - lastGotScore > COMBO_RESET_TIME)
		currentCombo = 0;
	lastGotScore = curTime;

	score += SCORE_COLLECT_BASE * std::min(++currentCombo, SCORE_COLLECT_MODIFIER_MAX);
	if (currentCombo > SCORE_COLLECT_MODIFIER_MAX)
		onGet1UP.Emit(++lives);
}

void GameState::Start() {
	clock.restart();
	score = 0;
	currentCombo = 0;
	lastGotScore = clock.getElapsedTime().asMilliseconds();
}
void GameState::Lose() {
	lives--;
}
