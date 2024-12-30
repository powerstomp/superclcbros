#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/View.hpp>

#include "../Entity/EntityFactory.h"
#include "../Entity/EntityManager.h"
#include "../Entity/Player/Player.h"
#include "../Entity/TileMap/TileMap.h"
#include "../Game.h"
#include "../GameState.h"
#include "State.h"

class StatePlay : public State {
private:
	enum class GameProgressState {
		ONGOING,
		ENDED,
		DISPOSABLE
	};
	std::string mapPath;

	sf::Text hudText;

	std::unique_ptr<GameState> gameState;
	EntityFactory entityFactory;
	Game* game;
	Player* player;
	sf::View view;
	std::unique_ptr<TileMap> tilemap, backgroundTilemap;
	EntityManager entityManager;
	PhysicsEngine physicsEngine;

	GameProgressState progressState = GameProgressState::ONGOING;

private:
	static std::unique_ptr<TileMap> LoadTileMapFromFile(
		const std::string& path, int mapWidth, int mapHeight
	);

	void UpdateView();
	void UpdateHUD();

public:
	StatePlay(Game*, std::unique_ptr<GameState> gameState, const std::string& mapPath);

	virtual void OnEnter() override;
	virtual void OnExit() override;
	virtual void Update() override;
	virtual void Render(double deltaTime) override;
	virtual void OnSFMLEvent(const sf::Event&) override;
};
