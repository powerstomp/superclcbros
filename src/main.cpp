#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <memory>

#include "Game.h"

constexpr int MICROSECONDS_PER_SECOND = 1000000;
constexpr int TICKS_PER_SECOND = 40;
constexpr int TIME_PER_TICK = MICROSECONDS_PER_SECOND / TICKS_PER_SECOND;

int main() {
	auto window = sf::RenderWindow({800, 600}, "Super CLC Bros");
	window.setFramerateLimit(144);

	std::unique_ptr<Game> game;

	sf::Clock clock;
	auto nextTickTime = clock.getElapsedTime().asMicroseconds();
	while (window.isOpen() && game->IsOpen()) {
		while (nextTickTime <= clock.getElapsedTime().asMicroseconds()) {
			for (sf::Event event; window.pollEvent(event);) {
				if (event.type == sf::Event::Closed)
					window.close();
			}
			game->Update();
			nextTickTime += TIME_PER_TICK;
		}
		double deltaTime =
			static_cast<double>(clock.getElapsedTime().asMicroseconds()) / TIME_PER_TICK;

		window.clear(sf::Color::Black);
		game->Render(deltaTime);
		window.display();
	}
}
