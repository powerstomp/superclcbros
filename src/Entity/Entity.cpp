#include "Entity.h"

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <iostream>
#include <stdexcept>

Entity::Entity(
	sf::Sprite sprite, sf::Vector2f position, double acceleration, double maxSpeed,
	double jumpVelocity, std::unique_ptr<EntityController> controller

)
	: sprite(sprite),
	  acceleration(acceleration),
	  maxSpeed(maxSpeed),
	  jumpVelocity(jumpVelocity),
	  controller(std::move(controller)) {
	this->sprite.setPosition(position);
	this->sprite.setTextureRect(sf::IntRect(0, 0, 0, 0));

	animationSets.push_back(AnimationSet{.match = []() { return true; }});
}

sf::Sprite& Entity::GetSprite() {
	return sprite;
}

void Entity::AddAnimation(std::unique_ptr<AnimationHandler> handler) {
	animationSets.back().animations.push_front(std::move(handler));
}

void Entity::AddAnimationSet(AnimationSet&& set) {
	animationSets.push_front(std::move(set));
}

void Entity::FlipSprite() {
	// Get the current texture rectangle
	sf::IntRect rect = sprite.getTextureRect();

	// Flip by inverting the width
	rect.left += rect.width;   // Shift the starting point to the right
	rect.width = -rect.width;  // Invert the width to flip horizontally

	sprite.setTextureRect(rect);
}

double Entity::GetJumpVelocity() const {
	return jumpVelocity;
}

void Entity::Update() {
	if (invulnerabilityTicks > 0)
		invulnerabilityTicks--;

	if (controller)
		controller->Update(*this);
	for (auto& set : animationSets) {
		if (!set.match())
			continue;
		for (auto& handler : set.animations)
			if (handler->Update(*this, sprite))
				break;
		break;
	}
	if (facing == Direction::RIGHT)
		FlipSprite();
}

void Entity::SetDead() {
	isDead = true;
	velocity.x = 0;
	velocity.y = 0;
}

bool Entity::CanMove() const {
	return true;
}

bool Entity::OnTakeDamage() {
	if (IsDead())
		return false;
	SetDead();
	return true;
}

bool Entity::TakeDamage() {
	if (invulnerabilityTicks > 0)
		return false;
	if (IsDead() || !OnTakeDamage())
		return false;

	invulnerabilityTicks = INVULNERABILITY_LENGTH;
	onDamaged.Emit(*this);
	if (IsDead())
		onDeath.Emit(*this);

	return true;
}
bool Entity::Kill() {
	return TakeDamage();
}

bool Entity::IsDead() const {
	return isDead;
}

bool Entity::IsAffectedByGravity() const {
	return true;
}
bool Entity::IsAffectedByTiles() const {
	return true;
}

void Entity::Jump() {
	if (!IsOnGround() || !CanMove())
		return;
	velocity.y = jumpVelocity;
	groundState = EntityGroundState::JUMPING;
	onJump.Emit(*this);
}

void Entity::MoveHorizontal(Direction direction) {
	if (!CanMove())
		return;
	double acceleration = this->acceleration;
	if (!IsOnGround())
		acceleration /= 5;
	if (direction == Direction::LEFT)
		velocity.x -= acceleration;
	else if (direction == Direction::RIGHT)
		velocity.x += acceleration;
	else
		throw std::invalid_argument("Invalid horizontal move direction.");
	if (facing == direction)
		return;
	facing = direction;
}

Direction Entity::GetFacing() const {
	return facing;
}
sf::Vector2f Entity::GetPosition() const {
	return sprite.getPosition();
}
sf::Vector2f Entity::GetVelocity() const {
	return velocity;
}
sf::FloatRect Entity::GetBoundingBox() const {
	return sprite.getGlobalBounds();
}
bool Entity::IsOnGround() const {
	return groundState == EntityGroundState::GROUND;
}

void Entity::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(sprite, states);
}
