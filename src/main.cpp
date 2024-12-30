#include <SFML/Audio.hpp>
#include <SFML/Audio/Music.hpp>
#include <chrono>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <thread>

#include "Entity/Animation/AnimationManager.h"
#include "Game.h"
#include "Settings.h"
#include "Utility/MusicManager.h"
#include "Utility/ServiceLocator.h"
#include "Utility/SoundManager.h"
#include "Utility/TextureManager.h"

int main() {
	// Provide services to our game
	ServiceLocator<Settings>::Set(std::make_unique<Settings>());
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

	auto music = std::make_unique<sf::Music>();
	if (!music->openFromFile("assets/01-main-theme-overworld.mp3"))
		throw std::runtime_error("Can't load music.");
	ServiceLocator<sf::Music>::Set(std::move(music));

	std::cout << "Services initialized.\n";

	// This thread checks for if sounds are loaded, but finished playing
	// Because sfml sounds stop playing when they are destructed,
	// sound manager stores sounds, then disposes of them when finished.
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
