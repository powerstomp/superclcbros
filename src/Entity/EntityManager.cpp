#include "EntityManager.h"

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <stdexcept>

#include "Entity.h"

void EntityManager::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	states.transform *= getTransform();
	for (const auto& entity : entities)
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

void EntityManager::Update(PhysicsEngine& physicsEngine, TileMap& tileMap) {
	for (auto& entity : entities) {
		entity->Update();
		physicsEngine.Update(*entity, tileMap);
	}
}
