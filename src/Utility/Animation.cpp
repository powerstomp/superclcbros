#include "Animation.h"

#include <SFML/Graphics/Sprite.hpp>
#include <initializer_list>
#include <stdexcept>

Animation::Animation(std::initializer_list<Frame> frames)
	: Animation(std::list<Frame>(frames)) {
}
Animation::Animation(std::list<Frame> frames) : frames{std::move(frames)} {
	if (this->frames.size() == 0)
		throw std::invalid_argument("Empty animation.");
	Reset();
}

void Animation::Reset() {
	timer = -1;
}
void Animation::Update(sf::Sprite& sprite) {
	int tmp = ++timer;
	for (auto& frame : frames) {
		if (tmp < frame.duration) {
			sprite.setTextureRect(frame.dimensions);
			return;
		}
		tmp -= frame.duration;
	}
	Reset();
	sprite.setTextureRect(frames.begin()->dimensions);
}
