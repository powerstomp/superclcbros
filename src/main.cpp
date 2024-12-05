#include <SFML/Audio.hpp>
#include <chrono>
#include <iostream>
#include <memory>
#include <thread>

#include "Entity/Animation/AnimationManager.h"
#include "Game.h"
#include "Utility/MusicManager.h"
#include "Utility/ServiceLocator.h"
#include "Utility/SoundManager.h"
#include "Utility/TextureManager.h"

int main() {
	ServiceLocator<TextureManager>::Set(std::make_unique<TextureManager>());
	ServiceLocator<SoundManager>::Set(std::make_unique<SoundManager>());
	ServiceLocator<MusicManager>::Set(std::make_unique<MusicManager>());

	auto font = std::make_unique<sf::Font>();
	if (!font->loadFromFile("assets/font2.ttf"))
		throw std::runtime_error("Can't load font.");
	ServiceLocator<sf::Font>::Set(std::move(font));

	auto animationManager = std::make_unique<AnimationManager>();
	if (!animationManager->Load("assets/animations.txt"))
		throw std::runtime_error("Can't load animations.");
	ServiceLocator<AnimationManager>::Set(std::move(animationManager));

	std::cout << "Services initialized.\n";

	std::thread([&soundManager = ServiceLocator<SoundManager>::Get()]() mutable {
		while (true) {
			soundManager.Update();

			std::this_thread::sleep_for(std::chrono::seconds(1));
		}
	}).detach();
	std::cout << "Audio update thread started.\n";

	auto game = std::make_unique<Game>();
	game->Run();
}
