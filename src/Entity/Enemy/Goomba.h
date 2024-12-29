#ifndef _GOOMBA_H
#define _GOOMBA_H

#include "Enemy.h"

class Goomba : public Enemy {
private:
	sf::Sprite LoadSprite();

protected:
	void OnCollide(Entity&, Direction) override;

public:
	Goomba(sf::Vector2f position, std::unique_ptr<EntityController> controller);
};

#endif
