#include "EntityManager.h"

#include <SFML/Graphics/RenderTarget.hpp>
#include <iostream>

void EntityManager::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	states.transform *= getTransform();
	for (auto& entity : entities)
		target.draw(*entity, states);
}

void EntityManager::AddEntity(std::unique_ptr<Entity> entity) {
	entities.push_back(std::move(entity));
}
void EntityManager::RemoveEntity(const Entity* entity) {
	// auto it = std::find(entities.begin(), entities.end(), entity);
	// if (it == entities.end())
	// 	throw std::invalid_argument("Can't remove unregistered entity.");
	// entities.erase(it);
}

void EntityManager::Update(TileMap& tileMap) {
	for (auto& entity : entities) {
		entity->Update();
		entity->position += entity->velocity;
		entity->sprite.setPosition(entity->GetPosition());
		entity->isOnGround = false;

		auto entityBB = entity->GetBoundingBox();
		const int minTileX = entityBB.left / TILE_SIZE,
				  maxTileX = (entityBB.left + entityBB.width) / TILE_SIZE;
		const int minTileY = entityBB.top / TILE_SIZE,
				  maxTileY = (entityBB.top + entityBB.height) / TILE_SIZE;

		for (auto x = minTileX; x <= maxTileX; x++) {
			for (auto y = minTileY; y <= maxTileY; y++) {
				auto tileType = tileMap.GetTile(x, y);
				if (tileType == TileType::NONE)
					continue;

				auto tileBB = tileMap.GetTileBoundingBox(x, y);
				tileBB.width += 2;
				tileBB.height += 2;
				tileBB.left -= 1;
				tileBB.top -= 1;
				sf::FloatRect intersection;
				if (!entityBB.intersects(tileBB, intersection))
					continue;

				float overlapX =
					std::min(entityBB.left + entityBB.width, tileBB.left + tileBB.width) -
					std::max(entityBB.left, tileBB.left);
				float overlapY =
					std::min(entityBB.top + entityBB.height, tileBB.top + tileBB.height) -
					std::max(entityBB.top, tileBB.top);

				// Determine the axis of intersection
				if (overlapX < overlapY) {
					if (entityBB.left < tileBB.left) {
						// Intersecting from the left
						entity->position.x -= overlapX;	 // Push left
						entity->velocity.x = 0;			 // Stop horizontal movement
					} else {
						// Intersecting from the right
						entity->position.x += overlapX;	 // Push right
						entity->velocity.x = 0;			 // Stop horizontal movement
					}
				} else {
					if (entityBB.top < tileBB.top) {
						// Intersecting from the top
						entity->position.y -= overlapY;	 // Push up
						entity->isOnGround = true;
						entity->velocity.y = 0;	 // Stop vertical movement
					} else {
						// Intersecting from the bottom
						entity->position.y += overlapY;	 // Push down
						entity->velocity.y = 0;			 // Stop vertical movement
					}
				}

				// Update the bounding box after position correction
				entity->sprite.setPosition(entity->GetPosition());
				entityBB = entity->GetBoundingBox();
			}
		}

		// Update the entity's sprite position to match its corrected position
		entity->sprite.setPosition(entity->GetPosition());
	}
}
