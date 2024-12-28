#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/View.hpp>

#include "../Entity/EntityManager.h"
#include "../Entity/Player/Player.h"
#include "../Entity/TileMap/TileMap.h"
#include "../Game.h"
#include "State.h"

class StatePlay : public State {
private:
	Game* game;
	Player* player;
	sf::View view;
	std::unique_ptr<TileMap> tilemap;
	EntityManager entityManager;
	PhysicsEngine physicsEngine;

private:
	void UpdateView();

public:
	StatePlay(Game*, const std::string& mapPath);

	virtual void OnEnter() override;
	virtual void Update() override;
	virtual void Render(double deltaTime) override;
	virtual void OnSFMLEvent(const sf::Event&) override;
};
