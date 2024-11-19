#ifndef _MUSICMANAGER_H
#define _MUSICMANAGER_H

#include <SFML/Audio/Music.hpp>

#include "AssetManager.h"

class MusicManager : public AssetManager<sf::Music> {};

#endif
