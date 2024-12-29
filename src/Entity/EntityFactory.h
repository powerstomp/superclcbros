#ifndef _ENTITYFACTORY_H
#define _ENTITYFACTORY_H

#include "Entity.h"

class StatePlay;
class GameState;

class EntityFactory {
private:
	enum EntityType {
		PLAYER,
		GOOMBA,
		PIRANHA,
		FLAG,
		ONE_UP,
		COIN
	};
	StatePlay& statePlay;
	GameState& gameState;

public:
	EntityFactory(StatePlay&, GameState&);

	std::unique_ptr<Entity> Create(int id, sf::Vector2f position);
};

#endif
