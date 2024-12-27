#include "PlayerController.h"

#include <SFML/Window/Keyboard.hpp>

#include "../Entity.h"

void PlayerController::Update(Entity& entity) {
	int horizontalControl = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) -
							sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A);
	if (horizontalControl == 1)
		entity.MoveHorizontal(Direction::RIGHT);
	else if (horizontalControl == -1)
		entity.MoveHorizontal(Direction::LEFT);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
		entity.Jump();
}
