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

	bool isDead = false;

	double acceleration, maxSpeed;
	double jumpVelocity;

	EntityGroundState groundState = EntityGroundState::GROUND;
	Direction facing = Direction::LEFT;

	std::unique_ptr<EntityController> controller;
	std::list<std::unique_ptr<AnimationHandler>> animations;

	void FlipSprite();

protected:
	sf::Vector2f velocity;

	double GetJumpVelocity() const;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	virtual bool CanMove() const;
	virtual bool IsAffectedByGravity() const;

	sf::Sprite& GetSprite();
	void AddAnimation(std::unique_ptr<AnimationHandler>);

	// Active voice. A attacks B -> A inflicts damage on B
	// => A::OnCollide does damage to B, NOT vice versa.
	virtual void OnCollide(Entity&, Direction) = 0;
	virtual bool OnTakeDamage();
	void SetDead();

public:
	Signal<Entity&> onDeath;
	Signal<Entity&> onDamaged;
	Signal<Entity&> onJump;

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

	virtual bool TakeDamage();
	virtual bool Kill();
	bool IsDead() const;

	Direction GetFacing() const;
	sf::Vector2f GetPosition() const;
	sf::Vector2f GetVelocity() const;
	sf::FloatRect GetBoundingBox() const;
	bool IsOnGround() const;
};

#endif
