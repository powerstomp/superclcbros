#ifndef _FLAG_H
#define _FLAG_H

#include <SFML/System/Vector2.hpp>

#include "../Entity.h"

class Flag : public Entity {
private:
	sf::Sprite LoadSprite();

protected:
	void OnCollide(Entity&, Direction) override;

public:
	Flag(sf::Vector2f position);
};

#endif
