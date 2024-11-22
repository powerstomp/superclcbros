#ifndef _MARIO_H
#define _MARIO_H

#include <SFML/Graphics/Sprite.hpp>

#include "../Utility/Animation.h"
#include "Player.h"

class Mario : public Player {
private:
	Animation animationRunning;

public:
	Mario(sf::Vector2f position);
	virtual void Update() override;
};

#endif
