#ifndef _PLAYER_H
#define _PLAYER_H

#include "../Entity.h"

class Enemy : public Entity {
public:
	Enemy(
		sf::Sprite sprite, sf::Vector2f position, double acceleration, double maxSpeed,
		double jumpVelocity, std::unique_ptr<EntityController> controller
	);
};

#endif
