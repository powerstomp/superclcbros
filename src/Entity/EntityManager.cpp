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
		entity->isOnGround = false;

		auto entityBB = entity->GetBoundingBox();
		entityBB.left += entity->velocity.x;
		entityBB.top += entity->velocity.y;

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
				sf::FloatRect intersection;
				if (!entityBB.intersects(tileBB, intersection))
					continue;

				float overlapX =
					std::min(entityBB.left + entityBB.width, tileBB.left + tileBB.width) -
					std::max(entityBB.left, tileBB.left);
				float overlapY =
					std::min(entityBB.top + entityBB.height, tileBB.top + tileBB.height) -
					std::max(entityBB.top, tileBB.top);

				if (overlapX < overlapY &&
					overlapY > std::abs(entity->velocity.y) + 1e-5) {
					if (entityBB.left < tileBB.left)
						entityBB.left -= overlapX;
					else
						entityBB.left += overlapX;
					entity->velocity.x = 0;
				}
			}
		}
		for (auto x = minTileX; x <= maxTileX; x++) {
			for (auto y = minTileY; y <= maxTileY; y++) {
				auto tileType = tileMap.GetTile(x, y);
				if (tileType == TileType::NONE)
					continue;

				auto tileBB = tileMap.GetTileBoundingBox(x, y);
				sf::FloatRect intersection;
				if (!entityBB.intersects(tileBB, intersection))
					continue;

				float overlapX =
					std::min(entityBB.left + entityBB.width, tileBB.left + tileBB.width) -
					std::max(entityBB.left, tileBB.left);
				float overlapY =
					std::min(entityBB.top + entityBB.height, tileBB.top + tileBB.height) -
					std::max(entityBB.top, tileBB.top);

				bool isCorner =
					std::abs(overlapX / tileBB.width - overlapY / tileBB.height) < 0.08;

				if (overlapX < overlapY) {
				} else {
					if (entityBB.top < tileBB.top) {
						entityBB.top -= overlapY;
						entity->isOnGround = true;
					} else
						entityBB.top += overlapY;
					if (isCorner)
						entity->velocity.y *= 0.7;
					else
						entity->velocity.y = 0;
				}
			}
		}
		entity->sprite.setPosition(entityBB.getPosition());
	}
}
