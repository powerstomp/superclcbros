#include "EntityManager.h"

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <iostream>

#include "Entity.h"

void EntityManager::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	states.transform *= getTransform();
	for (auto& entity : entities)
		target.draw(*entity, states);
}

void EntityManager::AddEntity(std::unique_ptr<Entity> entity) {
	entities.push_back(std::move(entity));
}
void EntityManager::RemoveEntity(const Entity* entity) {
	for (auto it = entities.begin(); it != entities.end(); it++) {
		if (it->get() == entity) {
			entities.erase(it);
			break;
		}
	}
	throw std::invalid_argument("Can't remove unregistered entity.");
}

// TODO: All entities should have at least one sprite attached
void EntityManager::Update(TileMap& tileMap) {
	for (auto& entity : entities) {
		entity->Update();

		entity->velocity.y += 1.25;
		entity->sprite.move(entity->velocity);

		entity->isOnGround = false;

		HandleMapCollision(*entity, tileMap, ResolveMapCollisionHorizontal);
		HandleMapCollision(*entity, tileMap, ResolveMapCollisionVertical);
	}
}

void EntityManager::ResolveMapCollisionHorizontal(
	Entity& entity, const CollisionResult& collisionResult
) {
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
void EntityManager::ResolveMapCollisionVertical(
	Entity& entity, const CollisionResult& collisionResult
) {
	if (collisionResult.direction == Direction::UP) {
		entity.sprite.move(0, collisionResult.overlap.y);

	} else if (collisionResult.direction == Direction::DOWN) {
		entity.sprite.move(0, -collisionResult.overlap.y);
		entity.isOnGround = true;
	}
	if (collisionResult.direction == Direction::UP ||
		collisionResult.direction == Direction::DOWN)
		entity.velocity.y = 0;
}

CollisionResult EntityManager::GetCollisionResult(
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

void EntityManager::HandleMapCollision(
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
