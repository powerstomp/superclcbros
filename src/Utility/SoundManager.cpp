#include "SoundManager.h"

#include <SFML/Audio/Sound.hpp>

void SoundManager::Play(const std::string& path) {
	sf::Sound sound;
	sound.setBuffer(GetOrLoad(path));
	sound.play();
	sounds.push_back(std::move(sound));
}

void SoundManager::Update() {
	for (auto it = sounds.begin(); it != sounds.end();) {
		if (it->getStatus() != sf::Sound::Status::Playing)
			it = sounds.erase(it);
		else
			it++;
	}
}
