#ifndef _LUIGI_H
#define _LUIGI_H

#include <SFML/Graphics/Sprite.hpp>

#include "Player.h"

class Luigi : public Player {
private:
	sf::Sprite GetSprite();

public:
	Luigi(sf::Vector2f position, std::unique_ptr<EntityController> controller);
};

#endif
