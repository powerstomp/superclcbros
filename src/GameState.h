#ifndef _GAMESTATE_H
#define _GAMESTATE_H

#include <SFML/System/Clock.hpp>

#include "Observer/Signal.h"

enum class PlayerType {
	MARIO,
	LUIGI
};

class GameState {
private:
	static constexpr int COMBO_RESET_TIME = 3000;
	static constexpr int COIN_VALUE = 200;
	static constexpr int SCORE_COLLECT_BASE = 500;
	static constexpr int SCORE_COLLECT_MODIFIER_MAX = 4;
	int lives = 3;
	int score;
	int currentCombo;
	sf::Clock clock;
	int lastGotScore;

	PlayerType playerType;

public:
	GameState(PlayerType playerType);
	Signal<int> onGet1UP;
	Signal<> onGetCoin;

	int GetLives() const;
	int GetTimeRemaining() const;
	int GetScore() const;

	PlayerType GetPlayerType() const;

	void OnKillEnemy();
	void OnCollectCoin();
	void OnCollect1UP();

	void Start();
	void Lose();
};

#endif
