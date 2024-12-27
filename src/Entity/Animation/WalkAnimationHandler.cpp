#include "WalkAnimationHandler.h"

#include <SFML/Graphics/Sprite.hpp>

#include "../Entity.h"

WalkAnimationHandler::WalkAnimationHandler(Animation animation)
	: AnimationHandler(animation) {
}

bool WalkAnimationHandler::Update(Entity& entity, sf::Sprite& sprite) {
	if (std::abs(entity.GetVelocity().x) < 0.5)
		return false;
	animation.Update(sprite);
	return true;
}
