#include <iostream>
#include <memory>

#include "Game.h"
#include "Utility/ServiceLocator.h"
#include "Utility/TextureManager.h"

int main() {
	ServiceLocator<TextureManager>::Set(std::make_unique<TextureManager>());
	auto font = std::make_unique<sf::Font>();
	if (!font->loadFromFile("assets/font2.ttf"))
		throw std::runtime_error("Can't load font.");
	ServiceLocator<sf::Font>::Set(std::move(font));
	std::cout << "Services initialized.\n";

	auto game = std::make_unique<Game>();
	game->Run();
}
