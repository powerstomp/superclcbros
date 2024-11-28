#ifndef _ENTITY_H
#define _ENTITY_H

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/System/Vector2.hpp>

class Entity : public sf::Drawable, public sf::Transformable {
	friend class PhysicsEngine;

protected:
	sf::Sprite sprite;
	sf::Vector2f velocity;

	bool isOnGround = false;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

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
};

#endif
