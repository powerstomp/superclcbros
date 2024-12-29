#include "SoundManager.h"

#include <SFML/Audio/Sound.hpp>

void SoundManager::Play(const std::string& path, std::function<void()> callback) {
	sf::Sound sound;
	sound.setBuffer(GetOrLoad(path));
	sounds.push_back(SoundWithCallback{std::move(sound), callback});
	sounds.back().sound.play();
}

void SoundManager::Update() {
	for (auto it = sounds.begin(); it != sounds.end();)
		if (it->sound.getStatus() != sf::Sound::Status::Playing) {
			it->callback();
			it = sounds.erase(it);
		} else
			it++;
}
