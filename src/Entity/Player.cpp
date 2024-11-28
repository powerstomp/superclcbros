#include "Player.h"

#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <cmath>
#include <iostream>

#include "../Definitions.h"
#include "Entity.h"

Player::Player(sf::Vector2f position) : Entity(position) {
}

void Player::Update() {
	constexpr auto ACCEL = 1;

	velocity.x *= 0.90;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
		velocity.x += ACCEL;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
		velocity.x -= ACCEL;
	// velocity.x -= std::copysign(20.0 / TICKS_PER_SECOND, velocity.x);
	if (velocity.x < -10)
		velocity.x = -10;
	if (velocity.x > 10)
		velocity.x = 10;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) && isOnGround)
		velocity.y = -23;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::G) && isOnGround)
		position.y += 40;
}
