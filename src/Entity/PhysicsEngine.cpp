#include "PhysicsEngine.h"

#include <SFML/Graphics/Rect.hpp>
#include <cmath>
#include <iostream>

#include "Entity.h"

void PhysicsEngine::ResolveMapCollisionHorizontal(
	Entity& entity, const CollisionResult& collisionResult
) {
	// Since we apply velocity then resolve, there is a chance we detect
	// a horizontal collision on flat ground. This prevents it by checking
	// if we are in a block by at least more than one tick of velocity.
	if (collisionResult.overlap.y < std::abs(entity.velocity.y) + 1e-5)
		return;
	if (collisionResult.direction == Direction::RIGHT)
		entity.sprite.move(-collisionResult.overlap.x, 0);
	else if (collisionResult.direction == Direction::LEFT)
		entity.sprite.move(collisionResult.overlap.x, 0);
	if (collisionResult.direction == Direction::LEFT ||
		collisionResult.direction == Direction::RIGHT)
		entity.velocity.x = 0;
}
void PhysicsEngine::ResolveMapCollisionVertical(
	Entity& entity, const CollisionResult& collisionResult
) {
	if (collisionResult.direction == Direction::UP) {
		entity.sprite.move(0, collisionResult.overlap.y);

	} else if (collisionResult.direction == Direction::DOWN) {
		entity.sprite.move(0, -collisionResult.overlap.y);
		entity.groundState = EntityGroundState::GROUND;
	}
	if (collisionResult.direction == Direction::UP ||
		collisionResult.direction == Direction::DOWN)
		entity.velocity.y = 0;
}

CollisionResult PhysicsEngine::GetCollisionResult(
	const sf::FloatRect& origin, const sf::FloatRect& target
) {
	sf::FloatRect intersection;
	if (!origin.intersects(target, intersection))
		return CollisionResult{};

	float overlapX = std::min(origin.left + origin.width, target.left + target.width) -
					 std::max(origin.left, target.left);
	float overlapY = std::min(origin.top + origin.height, target.top + target.height) -
					 std::max(origin.top, target.top);

	Direction direction = Direction::NONE;
	if (overlapX < overlapY) {
		if (origin.left < target.left)
			direction = Direction::RIGHT;
		else
			direction = Direction::LEFT;
	} else {
		if (origin.top < target.top)
			direction = Direction::DOWN;
		else
			direction = Direction::UP;
	}

	return CollisionResult{direction, intersection, {overlapX, overlapY}};
}

void PhysicsEngine::HandleMapCollision(
	Entity& entity, const TileMap& tileMap, MapCollisionResolver resolver
) {
	auto entityBB = entity.GetBoundingBox();

	const int minTileX = entityBB.left / TILE_SIZE,
			  maxTileX = (entityBB.left + entityBB.width) / TILE_SIZE;
	const int minTileY = entityBB.top / TILE_SIZE,
			  maxTileY = (entityBB.top + entityBB.height) / TILE_SIZE;

	for (auto x = minTileX; x <= maxTileX; x++) {
		for (auto y = minTileY; y <= maxTileY; y++) {
			auto tileType = tileMap.GetTile(x, y);
			if (tileType == TileType::NONE)
				continue;

			auto entityBB = entity.GetBoundingBox();
			auto tileBB = tileMap.GetTileBoundingBox(x, y);

			resolver(entity, GetCollisionResult(entityBB, tileBB));
		}
	}
}

void PhysicsEngine::Update(Entity& entity, const TileMap& tileMap) {
	if (!entity.IsOnGround())
		entity.velocity.x *= AIR_FRICTION;
	else
		entity.velocity.x *= FRICTION;

	if (entity.IsAffectedByGravity())
		entity.velocity.y += GRAVITY;

	if (entity.velocity.x < -entity.maxSpeed)
		entity.velocity.x = -entity.maxSpeed;
	if (entity.velocity.x > entity.maxSpeed)
		entity.velocity.x = entity.maxSpeed;

	if (entity.velocity.y > TERMINAL_VELOCITY)
		entity.velocity.y = TERMINAL_VELOCITY;

	entity.sprite.move(entity.velocity);

	if (entity.groundState == EntityGroundState::GROUND)
		entity.groundState = EntityGroundState::AIR;

	if (!entity.IsAffectedByTiles())
		return;

	// Apply horizontally then vertically to avoid getting stuck in blocks
	HandleMapCollision(entity, tileMap, ResolveMapCollisionHorizontal);
	HandleMapCollision(entity, tileMap, ResolveMapCollisionVertical);

	// HandleMapCollision(entity, tileMap, ResolveMapCollisionVertical);
	// HandleMapCollision(entity, tileMap, ResolveMapCollisionHorizontal);
}

void PhysicsEngine::Update(Entity& a, Entity& b) {
	auto aBox = a.GetBoundingBox(), bBox = b.GetBoundingBox();
	bBox.top -= 1;

	auto collisionResult = GetCollisionResult(a.GetBoundingBox(), bBox);
	if (collisionResult.direction == Direction::NONE)
		return;
	a.OnCollide(b, collisionResult.direction);
	b.OnCollide(a, GetOppositeDirection(collisionResult.direction));
}
