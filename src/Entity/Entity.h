#ifndef _ENTITY_H
#define _ENTITY_H

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/System/Vector2.hpp>
#include <memory>

#include "../Observer/Signal.h"
#include "Animation/AnimationHandler.h"
#include "Controller/EntityController.h"
#include "PhysicsEngine.h"

enum class EntityGroundState {
	GROUND,
	AIR,
	JUMPING
};

class Entity : public sf::Drawable {
private:
	friend class PhysicsEngine;

	sf::Sprite sprite;
	sf::Vector2f velocity;

	bool isDead;

	double acceleration, maxSpeed;
	double jumpVelocity;

	EntityGroundState groundState = EntityGroundState::GROUND;
	Direction facing = Direction::LEFT;

	std::unique_ptr<EntityController> controller;
	std::list<std::unique_ptr<AnimationHandler>> animations;

	void FlipSprite();

protected:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	sf::Sprite& GetSprite();
	void AddAnimation(std::unique_ptr<AnimationHandler>);
	virtual void OnCollide(Entity&, Direction) = 0;
	virtual void OnTakeDamage();
	void SetDead();

public:
	Signal<Entity&> onDeath;
	Signal<Entity&> onDamaged;

	Entity(
		sf::Sprite sprite, sf::Vector2f position, double acceleration, double maxSpeed,
		double jumpVelocity, std::unique_ptr<EntityController> controller
	);
	virtual ~Entity() = default;
	Entity(const Entity&) = delete;
	Entity& operator=(const Entity&) = delete;
	Entity(Entity&&) = default;
	Entity& operator=(Entity&&) = default;

	void Update();
	void Jump();
	void MoveHorizontal(Direction);

	virtual void TakeDamage();
	bool IsDead() const;

	Direction GetFacing() const;
	sf::Vector2f GetPosition() const;
	sf::Vector2f GetVelocity() const;
	sf::FloatRect GetBoundingBox() const;
	bool IsOnGround() const;
};

#endif
