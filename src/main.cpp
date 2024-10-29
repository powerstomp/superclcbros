#include <SFML/Graphics.hpp>
#include <SFML/Window/Event.hpp>

int main() {
	auto window = sf::RenderWindow({800, 600}, "Super CLC Bros");
	window.setVerticalSyncEnabled(true);

	while (window.isOpen()) {
		for (sf::Event event; window.pollEvent(event);) {
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear(sf::Color::Black);
		window.display();
	}
}
