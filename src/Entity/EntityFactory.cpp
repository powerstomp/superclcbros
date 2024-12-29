#include "EntityFactory.h"

#include <iostream>
#include <memory>
#include <stdexcept>

#include "../GameState.h"
#include "Controller/PlayerController.h"
#include "Controller/SimpleAIController.h"
#include "Enemy/Goomba.h"
#include "Enemy/Piranha.h"
#include "Misc/Flag.h"
#include "Player/Luigi.h"
#include "Player/Mario.h"

EntityFactory::EntityFactory(StatePlay& statePlay, GameState& gameState)
	: statePlay(statePlay), gameState(gameState) {
}

std::unique_ptr<Entity> EntityFactory::Create(int id, sf::Vector2f position) {
	EntityType type = static_cast<EntityType>(id);
	switch (type) {
	case PLAYER:
		if (gameState.GetPlayerType() == PlayerType::MARIO)
			return std::make_unique<Mario>(
				position, std::make_unique<PlayerController>()
			);
		else if (gameState.GetPlayerType() == PlayerType::LUIGI)
			return std::make_unique<Luigi>(
				position, std::make_unique<PlayerController>()
			);
	case GOOMBA:
		return std::make_unique<Goomba>(position, std::make_unique<SimpleAIController>());
	case PIRANHA:
		return std::make_unique<Piranha>(position);
	case FLAG:
		return std::make_unique<Flag>(position);
	default:
		throw std::invalid_argument("Unknown entity type.");
	}
}
