#include "SoundManager.h"

#include <SFML/Audio/Sound.hpp>

#include "../Settings.h"
#include "ServiceLocator.h"

void SoundManager::Play(const std::string& path, std::function<void()> callback) {
	sf::Sound sound;
	sound.setBuffer(GetOrLoad(path));
	if (!ServiceLocator<Settings>::Get().IsSoundEffectsEnabled())
		sound.setVolume(0);
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
