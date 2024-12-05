#include "StatePlay.h"

#include <SFML/Graphics/Font.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>

#include "../Entity/Player/Mario.h"

// TODO: Temporary
static const char* tileData[] = {
	"0000000000000000", "0000000002000000", "0000000000000000", "0000000222220000",
	"0000000000000000", "1111011111110011", "1111001101001001", "1111100100010011",
	"0000000001000000", "0000000000000000", "1111111100011111", "1111111100010001"
};

StatePlay::StatePlay(Game* game) : game{game}, tilemap(tileData, 16, 12) {
	entityManager.AddEntity(std::make_unique<Mario>(sf::Vector2f(30, 30)));
}

void StatePlay::OnEnter() {
	game->window.setView(game->window.getDefaultView());
}
void StatePlay::Update() {
	entityManager.Update(physicsEngine, tilemap);
}

void StatePlay::Render(double deltaTime) {
	game->window.draw(tilemap);
	game->window.draw(entityManager);
}
void StatePlay::OnSFMLEvent(const sf::Event& event) {
	if (event.type == sf::Event::KeyPressed)
		if (event.key.code == sf::Keyboard::Key::Escape)
			game->PopState();
}
