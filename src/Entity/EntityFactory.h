#ifndef _ENTITYFACTORY_H
#define _ENTITYFACTORY_H

#include "Entity.h"
#include "Pickup/LuckyBlock.h"

class StatePlay;
class GameState;

enum EntitySpawnType {
	PLAYER,
	GOOMBA,
	PIRANHA,
	FLAG,
	ONE_UP,
	COIN,
	BLOCK_COIN,
	BLOCK_MUSHROOM
};

class EntityFactory {
private:
	StatePlay& statePlay;
	GameState& gameState;

public:
	EntityFactory(StatePlay&, GameState&);

	std::unique_ptr<Entity> Create(int id, sf::Vector2f position);
	std::unique_ptr<Entity> CreateFromLuckyBlockType(
		LuckyBlockType type, sf::Vector2f position
	);
};

#endif
