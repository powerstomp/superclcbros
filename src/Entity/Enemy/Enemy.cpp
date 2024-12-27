#include "Enemy.h"

Enemy::Enemy(
	sf::Sprite sprite, sf::Vector2f position, double acceleration, double maxSpeed,
	double jumpVelocity, std::unique_ptr<EntityController> controller
)
	: Entity(
		  sprite, position, acceleration, maxSpeed, jumpVelocity, std::move(controller)
	  ) {
}
