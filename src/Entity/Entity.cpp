#include "Entity.h"

Entity::Entity(sf::Vector2f position) : position{position} {
}

sf::Vector2f Entity::GetPosition() const {
	return position;
}
sf::FloatRect Entity::GetBoundingBox() const {
	return GetSprite()->getLocalBounds();
}
