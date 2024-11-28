#include "Entity.h"

#include <SFML/Graphics/RenderTarget.hpp>

Entity::Entity(sf::Vector2f position) {
	sprite.setPosition(position);
}

sf::Vector2f Entity::GetPosition() const {
	return sprite.getPosition();
}
sf::FloatRect Entity::GetBoundingBox() const {
	return sprite.getGlobalBounds();
}

void Entity::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(sprite, states);
}
