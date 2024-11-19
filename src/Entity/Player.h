#ifndef _PLAYER_H
#define _PLAYER_H

#include "Entity.h"

enum PlayerModifier {
	NORMAL,
	LARGE,
	FIREPOWER
};

class Player : public Entity {
protected:
	PlayerModifier modifier = PlayerModifier::NORMAL;

public:
	Player(sf::Vector2f position);
};

#endif
