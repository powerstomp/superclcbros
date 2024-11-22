#include "Entity.h"

#include <SFML/Graphics/RenderTarget.hpp>

Entity::Entity(sf::Vector2f position) : position{position} {
}

sf::Vector2f Entity::GetPosition() const {
	return position;
}
sf::FloatRect Entity::GetBoundingBox() const {
	return sprite.getGlobalBounds();
}

void Entity::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	states.transform *= getTransform();
	target.draw(sprite, states);
}
