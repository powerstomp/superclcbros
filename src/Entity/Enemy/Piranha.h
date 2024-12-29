#ifndef _PIRANHA_H
#define _PIRANHA_H

#include "Enemy.h"

class Piranha : public Enemy {
private:
	sf::Sprite GetSprite();

protected:
	void OnCollide(Entity&, Direction) override;
	bool OnTakeDamage() override;

public:
	Piranha(sf::Vector2f position);
};

#endif
