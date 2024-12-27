#ifndef _MARIO_H
#define _MARIO_H

#include <SFML/Graphics/Sprite.hpp>

#include "Player.h"

class Mario : public Player {
private:
	sf::Sprite GetSprite();

public:
	Mario(sf::Vector2f position, std::unique_ptr<EntityController> controller);
};

#endif
