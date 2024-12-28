#include "Player.h"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <cmath>

#include "../Controller/PlayerController.h"
#include "../Enemy/Enemy.h"

Player::Player(
	sf::Sprite sprite, sf::Vector2f position, double acceleration, double maxSpeed,
	double jumpVelocity, std::unique_ptr<EntityController> controller
)
	: Entity(
		  sprite, position, acceleration, maxSpeed, jumpVelocity, std::move(controller)
	  ) {
}

void Player::OnCollide(Entity& entity, Direction direction) {
	if (auto enemy = dynamic_cast<Enemy*>(&entity)) {
		if (direction == Direction::DOWN) {
			enemy->TakeDamage();
			onHitEnemy.Emit(*enemy);
		}
	}
}

void Player::OnTakeDamage() {
	if (modifier != PlayerModifier::NORMAL)
		modifier = PlayerModifier::NORMAL;
	else
		SetDead();
}

PlayerModifier Player::GetModifier() const {
	return modifier;
}

bool Player::CanUpdateModifier(PlayerModifier modifier) const {
	switch (this->modifier) {
	case PlayerModifier::NORMAL:
		if (modifier == PlayerModifier::LARGE)
			return true;
	case PlayerModifier::LARGE:
		if (modifier == PlayerModifier::FIREPOWER)
			return true;
	default:
		return false;
	}
}

void Player::OnGetModifier(PlayerModifier modifier) {
	if (CanUpdateModifier(modifier))
		this->modifier = modifier;
}
