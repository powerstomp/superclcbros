#ifndef _SOUNDMANAGER_H
#define _SOUNDMANAGER_H

#include <SFML/Audio/SoundBuffer.hpp>
#include <list>

#include "AssetManager.h"

class SoundManager : public AssetManager<sf::SoundBuffer> {
private:
	std::list<sf::Sound> sounds;

public:
	void Play(const std::string&);
	void Update();
};

#endif
