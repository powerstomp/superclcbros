#include "EntityFactory.h"

#include <SFML/System/Vector2.hpp>
#include <iostream>
#include <memory>
#include <stdexcept>

#include "../GameState.h"
#include "Controller/PlayerController.h"
#include "Controller/SimpleAIController.h"
#include "Enemy/Goomba.h"
#include "Enemy/Piranha.h"
#include "Misc/Flag.h"
#include "Pickup/CoinItem.h"
#include "Pickup/LuckyBlock.h"
#include "Pickup/MushroomItem.h"
#include "Pickup/OneUpItem.h"
#include "Player/Luigi.h"
#include "Player/Mario.h"

EntityFactory::EntityFactory(StatePlay& statePlay, GameState& gameState)
	: statePlay(statePlay), gameState(gameState) {
}

std::unique_ptr<Entity> EntityFactory::Create(int id, sf::Vector2f position) {
	EntitySpawnType type = static_cast<EntitySpawnType>(id);
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
		return std::make_unique<Piranha>(position + sf::Vector2f(TILE_SIZE * 0.5, 0));
	case FLAG:
		return std::make_unique<Flag>(position);
	case ONE_UP:
		return std::make_unique<OneUpItem>(
			position, std::make_unique<SimpleAIController>()
		);
	case COIN:
		return std::make_unique<CoinItem>(position, nullptr);
	case BLOCK_COIN:
		return std::make_unique<LuckyBlock>(
			position + sf::Vector2f(0, 50), LuckyBlockType::COIN
		);
	case BLOCK_MUSHROOM:
		return std::make_unique<LuckyBlock>(
			position + sf::Vector2f(0, 50), LuckyBlockType::MUSHROOM
		);
	default:
		std::cerr << "Unknown entity type: " << id << '\n';
		return nullptr;
		// throw std::invalid_argument("Unknown entity type.");
	}
}

std::unique_ptr<Entity> EntityFactory::CreateFromLuckyBlockType(
	LuckyBlockType type, sf::Vector2f position
) {
	switch (type) {
	case LuckyBlockType::MUSHROOM: {
		auto result = std::make_unique<MushroomItem>(
			position, std::make_unique<SimpleAIController>()
		);
		result->Jump();
		return result;
	}
	default:
		std::cerr << "Unknown entity type: " << (int)type << '\n';
		return nullptr;
	}
}
