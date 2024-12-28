#include "Enemy.h"

#include "../Player/Player.h"

Enemy::Enemy(
	sf::Sprite sprite, sf::Vector2f position, double acceleration, double maxSpeed,
	double jumpVelocity, std::unique_ptr<EntityController> controller
)
	: Entity(
		  sprite, position, acceleration, maxSpeed, jumpVelocity, std::move(controller)
	  ) {
}

void Enemy::OnCollide(Entity& entity, Direction direction) {
	if (auto enemy = dynamic_cast<Player*>(&entity))
		if (direction != Direction::UP)
			enemy->TakeDamage();
}
