#ifndef _ANIMATION_H
#define _ANIMATION_H

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <initializer_list>
#include <list>

class Animation {
public:
	struct Frame {
		int duration;
		sf::IntRect dimensions;
	};

private:
	int timer;
	std::list<Frame> frames;

public:
	Animation(std::initializer_list<Frame>);
	void Reset();
	void Update(sf::Sprite&);
};

#endif
