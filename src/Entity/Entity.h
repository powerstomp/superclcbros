#ifndef _ENTITY_H
#define _ENTITY_H

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Vector2.hpp>

class Entity {
protected:
	sf::Vector2f position;

public:
	Entity(sf::Vector2f position);

	virtual ~Entity() = default;
	Entity(const Entity&) = default;
	Entity& operator=(const Entity&) = default;
	Entity(Entity&&) = default;
	Entity& operator=(Entity&&) = default;

	virtual void Update() = 0;

	sf::Vector2f GetPosition() const;
	sf::FloatRect GetBoundingBox() const;
	virtual const sf::Sprite* const GetSprite() const = 0;
};

#endif
