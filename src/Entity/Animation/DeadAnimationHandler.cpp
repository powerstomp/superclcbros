#include "DeadAnimationHandler.h"

#include "../Entity.h"

DeadAnimationHandler::DeadAnimationHandler(Animation animation)
	: AnimationHandler(animation) {
}

bool DeadAnimationHandler::Update(Entity& entity, sf::Sprite& sprite) {
	if (!entity.IsDead())
		return false;
	animation.Update(sprite);
	return true;
}
