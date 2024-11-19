#ifndef _MARIO_H
#define _MARIO_H

#include <SFML/Graphics/Sprite.hpp>

#include "../Utility/Animation.h"
#include "Player.h"

class Mario : public Player {
private:
	Animation animationStanding;
	Animation animationRunning;
	sf::Sprite sprite;

public:
	Mario(sf::Vector2f position);
	void Update() override;
	const sf::Sprite* const GetSprite() const override;
};

#endif
