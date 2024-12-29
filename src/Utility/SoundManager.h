#ifndef _SOUNDMANAGER_H
#define _SOUNDMANAGER_H

#include <SFML/Audio.hpp>
#include <functional>
#include <list>

#include "AssetManager.h"

class SoundManager : public AssetManager<sf::SoundBuffer> {
private:
	static inline const std::function<void()> EMPTY_CALLBACK = []() {};
	struct SoundWithCallback {
		sf::Sound sound;
		std::function<void()> callback;
	};
	std::list<SoundWithCallback> sounds;

public:
	void Play(const std::string&, std::function<void()> callback = EMPTY_CALLBACK);
	void Update();
};

#endif
