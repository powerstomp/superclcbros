#include "StatePlay.h"

#include <SFML/Graphics/Font.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <fstream>
#include <iostream>
#include <memory>
#include <stdexcept>

#include "../Entity/Controller/PlayerController.h"
#include "../Entity/Player/Mario.h"
#include "../Utility/CSVMapLoader.h"
#include "../Utility/ServiceLocator.h"
#include "../Utility/TextureManager.h"

StatePlay::StatePlay(Game* game, const std::string& mapPath) : game{game} {
	std::ifstream mapFile(mapPath);
	if (!mapFile.good())
		throw std::invalid_argument("Can't load map.");
	auto mapData = CSV::Parse(mapFile, 12, 300);

	std::cout << ServiceLocator<TextureManager>::Get()
					 .GetOrLoad("assets/objects.png")
					 .getSize()
					 .x
			  << '\n';

	auto tileset = Tileset{
		.texture = ServiceLocator<TextureManager>::Get().GetOrLoad("assets/objects.png"),
		.tileSize = 16,
		.n = 6,
		.m = 22,
		.margin = 3,
		.spacing = 1,
	};

	tilemap = std::make_unique<TileMap>(mapData, 300, 12, tileset);

	auto tmp = std::make_unique<Mario>(
		sf::Vector2f(30, 30), std::make_unique<PlayerController>()
	);
	player = tmp.get();
	entityManager.AddEntity(std::move(tmp));
}

void StatePlay::UpdateView() {
	sf::Vector2f center = player->GetPosition();
	center.x = std::max(center.x, view.getSize().x / 2);
	center.y = view.getSize().y / 2;
	view.setCenter(center);
	game->window.setView(view);
}

void StatePlay::OnEnter() {
	view = game->window.getDefaultView();
}
void StatePlay::Update() {
	entityManager.Update(physicsEngine, *tilemap);
}

void StatePlay::Render(double deltaTime) {
	UpdateView();

	game->window.draw(*tilemap);
	game->window.draw(entityManager);
}
void StatePlay::OnSFMLEvent(const sf::Event& event) {
	if (event.type == sf::Event::KeyPressed)
		if (event.key.code == sf::Keyboard::Key::Escape)
			game->PopState();
}
