#ifndef _GAMESTATE_H
#define _GAMESTATE_H

#include "Entity/EntityManager.h"
class GameState {
private:
	int lives;

public:
	int GetLives() const;
};

#endif
