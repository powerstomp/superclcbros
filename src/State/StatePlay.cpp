#include "StatePlay.h"

#include <SFML/Audio/Music.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <fstream>
#include <iostream>
#include <memory>
#include <stdexcept>

#include "../Entity/Misc/Flag.h"
#include "../Entity/Pickup/CoinItem.h"
#include "../Entity/Pickup/OneUpItem.h"
#include "../Settings.h"
#include "../Utility/CSVMapLoader.h"
#include "../Utility/ServiceLocator.h"
#include "../Utility/SoundManager.h"
#include "../Utility/TextureManager.h"

std::unique_ptr<TileMap> StatePlay::LoadTileMapFromFile(
	const std::string& path, int mapWidth, int mapHeight
) {
	std::ifstream mapFile(path);
	if (!mapFile.good())
		throw std::invalid_argument("Can't load map: " + path);
	auto mapData = CSV::Parse(mapFile, mapHeight, mapWidth);

	auto tileset = Tileset{
		.texture = ServiceLocator<TextureManager>::Get().GetOrLoad("assets/objects.png"),
		.tileSize = 16,
		.n = 6,
		.m = 22,
		.margin = 3,
		.spacing = 1,
	};

	return std::make_unique<TileMap>(mapData, mapWidth, mapHeight, tileset);
}

StatePlay::StatePlay(
	Game* game, std::unique_ptr<GameState> gameState, const std::string& mapPath
)
	: game{game},
	  gameState(std::move(gameState)),
	  mapPath(mapPath),
	  entityFactory(*this, *this->gameState) {
	int mapWidth, mapHeight;
	std::ifstream mapInfo(mapPath + "_Info.txt");
	if (!mapInfo.good())
		throw std::invalid_argument("Map not found.");
	if (!(mapInfo >> mapWidth >> mapHeight))
		throw std::invalid_argument("Can't load map info.");

	tilemap = LoadTileMapFromFile(mapPath + "_Terrain.csv", mapWidth, mapHeight);
	backgroundTilemap =
		LoadTileMapFromFile(mapPath + "_Background.csv", mapWidth, mapHeight);

	std::ifstream entitySpawnFile(mapPath + "_Entities.csv");
	if (!entitySpawnFile.good())
		throw std::invalid_argument("Can't load entities map.");
	auto entityData = CSV::Parse(entitySpawnFile, mapHeight, mapWidth);

	auto& gameStateRef = *this->gameState;
	gameStateRef.onGet1UP.Reset();

	bool foundPlayer = false, foundFlag = false;
	for (int i = 0; i < mapHeight; i++) {
		for (int j = 0; j < mapWidth; j++) {
			if (entityData[i][j] == -1)
				continue;
			auto entity =
				entityFactory.Create(entityData[i][j], tilemap->GetTilePosition(j, i));
			if (!entity)
				continue;
			if (auto player = dynamic_cast<Player*>(entity.get())) {
				foundPlayer = true;
				this->player = player;
			} else if (dynamic_cast<Flag*>(entity.get()))
				foundFlag = true;
			else if (auto oneUp = dynamic_cast<OneUpItem*>(entity.get()))
				oneUp->onPickup.Connect([&gameStateRef](PickupItem&) {
					gameStateRef.OnCollect1UP();
				});
			else if (auto coin = dynamic_cast<CoinItem*>(entity.get()))
				coin->onPickup.Connect([&gameStateRef](PickupItem&) {
					gameStateRef.OnCollectCoin();
				});
			else if (auto luckyBlock = dynamic_cast<LuckyBlock*>(entity.get())) {
				luckyBlock->onPickup.Connect([&](PickupItem& pickupItem) mutable {
					auto& luckyBlock = static_cast<LuckyBlock&>(pickupItem);
					if (luckyBlock.GetType() == LuckyBlockType::COIN)
						gameStateRef.OnCollectCoin();
					else {
						auto lol = entityFactory.CreateFromLuckyBlockType(
							luckyBlock.GetType(), luckyBlock.GetPosition()
						);
						entityManager.AddEntity(std::move(lol));
					}
				});
			}
			entityManager.AddEntity(std::move(entity));
		}
	}
	if (!foundPlayer)
		throw std::invalid_argument("Missing player.");
	if (!foundFlag)
		throw std::invalid_argument("Missing flag.");

	player->onHitEnemy.Connect([&gameStateRef](Enemy& entity) {
		ServiceLocator<SoundManager>::Get().Play("assets/smb_stomp.wav");
		gameStateRef.OnKillEnemy();
	});
	player->onJump.Connect([](Entity&) {
		ServiceLocator<SoundManager>::Get().Play("assets/smb_jump-small.wav");
	});
	player->onDeath.Connect([&](Entity&) mutable {
		ServiceLocator<sf::Music>::Get().stop();
		ServiceLocator<SoundManager>::Get().Play(
			"assets/smb_mariodie.wav",
			[&]() mutable { progressState = GameProgressState::DISPOSABLE; }
		);
		gameStateRef.Lose();
		progressState = GameProgressState::ENDED;
	});
	player->onTouchFlag.Connect([&]() mutable {
		ServiceLocator<sf::Music>::Get().stop();
		ServiceLocator<SoundManager>::Get().Play(
			"assets/smb_stage_clear.wav",
			[&]() mutable { progressState = GameProgressState::DISPOSABLE; }
		);
	});
	player->onGetModifier.Connect([&](PlayerModifier) mutable {
		ServiceLocator<SoundManager>::Get().Play("assets/smb_powerup.wav");
	});
	player->onDamaged.Connect([](Entity& entity) {
		if (!entity.IsDead())
			ServiceLocator<SoundManager>::Get().Play("assets/damage.wav");
	});

	gameStateRef.onGet1UP.Connect([](int lives) {
		ServiceLocator<SoundManager>::Get().Play("assets/smb_1-up.wav");
	});
	gameStateRef.onGetCoin.Connect([]() {
		ServiceLocator<SoundManager>::Get().Play("assets/smb_coin.wav");
	});

	hudText.setPosition(5, 5);
	hudText.setFont(ServiceLocator<sf::Font>::Get());
	hudText.setFillColor(sf::Color::White);
	hudText.setOutlineColor(sf::Color::Black);
}

void StatePlay::UpdateView() {
	sf::Vector2f center = player->GetPosition();
	center.x = TILE_SIZE + std::max(center.x, view.getSize().x / 2);
	center.y = view.getSize().y / 2;
	view.setCenter(center);
}

void StatePlay::OnEnter() {
	view = game->window.getDefaultView();
	if (ServiceLocator<Settings>::Get().IsMusicEnabled())
		ServiceLocator<sf::Music>::Get().play();
	gameState->Start();
}

void StatePlay::OnExit() {
	ServiceLocator<sf::Music>::Get().stop();
}

void StatePlay::Update() {
	entityManager.Update(physicsEngine, *tilemap);
	if (progressState == GameProgressState::ONGOING) {
		if (player->GetPosition().y > WINDOW_HEIGHT + 150 ||
			gameState->GetTimeRemaining() <= 0)
			player->Kill();
	} else if (progressState == GameProgressState::DISPOSABLE) {
		if (player->IsDead())
			game->StartGame(mapPath, std::move(gameState));
		else
			game->PopState();
	}
}

void StatePlay::UpdateHUD() {
	hudText.setString(
		"Lives " + std::to_string(gameState->GetLives()) + " Time " +
		std::to_string(gameState->GetTimeRemaining()) + " Coins " +
		std::to_string(gameState->GetScore())
	);
}

void StatePlay::Render(double deltaTime) {
	UpdateView();

	game->window.setView(view);
	game->window.draw(*backgroundTilemap);
	game->window.draw(*tilemap);
	game->window.draw(entityManager);

	UpdateHUD();

	game->window.setView(game->window.getDefaultView());
	game->window.draw(hudText);
}
void StatePlay::OnSFMLEvent(const sf::Event& event) {
	if (event.type == sf::Event::KeyPressed) {
		if (progressState != GameProgressState::ONGOING)
			return;
		if (event.key.code == sf::Keyboard::Key::Escape)
			game->PopState();
		else if (event.key.code == sf::Keyboard::Key::Tilde)
			player->Kill();
	}
}
