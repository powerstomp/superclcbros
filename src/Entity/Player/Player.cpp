#include "Player.h"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <cmath>

#include "../Enemy/Enemy.h"
#include "../Misc/Flag.h"

Player::Player(
	sf::Sprite sprite, sf::Vector2f position, double acceleration, double maxSpeed,
	double jumpVelocity, std::unique_ptr<EntityController> controller
)
	: Entity(
		  sprite, position, acceleration, maxSpeed, jumpVelocity, std::move(controller)
	  ) {
}

void Player::OnCollide(Entity& entity, Direction direction) {
	if (touchedFlag || IsDead())
		return;
	if (auto enemy = dynamic_cast<Enemy*>(&entity)) {
		if (direction == Direction::DOWN && enemy->TakeDamage()) {
			velocity.y = GetJumpVelocity() * 0.2;
			onHitEnemy.Emit(*enemy);
		}
	} else if (auto flag = dynamic_cast<Flag*>(&entity)) {
		if (flag->Kill()) {
			touchedFlag = true;
			velocity.y = 0;
			velocity.x = 4;
			onTouchFlag.Emit();
		}
	}
}

bool Player::Kill() {
	if (IsDead())
		return false;
	this->modifier = PlayerModifier::NORMAL;
	return Entity::Kill();
}

bool Player::OnTakeDamage() {
	if (IsDead() || touchedFlag)
		return false;
	if (modifier != PlayerModifier::NORMAL)
		modifier = PlayerModifier::NORMAL;
	else
		SetDead();
	return true;
}

PlayerModifier Player::GetModifier() const {
	return modifier;
}

bool Player::CanMove() const {
	return !IsDead() && !touchedFlag;
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
	if (CanUpdateModifier(modifier)) {
		this->modifier = modifier;
		onGetModifier.Emit(modifier);
	}
}
