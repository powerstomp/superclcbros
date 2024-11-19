#include "StatePlay.h"

#include <SFML/Graphics/Font.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>

// TODO: Temporary
static const char* tileData[] = {
	"0000000000000000", "0000000002000000", "0000000000000000", "0000000222220000",
	"0000000000000000", "1111011111111111", "1111001101001111", "1111100100011111",
	"0000000001000000", "0000000000000000", "1111111100011111", "1111111100011111"
};

StatePlay::StatePlay(Game* game)
	: game{game}, tilemap(tileData, 16, 12), mario(sf::Vector2f(40, 40)) {
}

void StatePlay::OnEnter() {
	game->window.setView(game->window.getDefaultView());
}
void StatePlay::Update() {
	mario.Update();
}

void StatePlay::Render(double deltaTime) {
	game->window.draw(tilemap);
	game->window.draw(*mario.GetSprite());
}
void StatePlay::OnSFMLEvent(const sf::Event& event) {
	if (event.type == sf::Event::KeyPressed)
		if (event.key.code == sf::Keyboard::Key::Escape)
			game->PopState();
}
