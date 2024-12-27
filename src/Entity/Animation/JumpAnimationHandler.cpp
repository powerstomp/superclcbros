#include "JumpAnimationHandler.h"

#include "../Entity.h"

JumpAnimationHandler::JumpAnimationHandler(Animation animation)
	: AnimationHandler(animation) {
}

bool JumpAnimationHandler::Update(Entity& entity, sf::Sprite& sprite) {
	if (entity.IsOnGround())
		return false;
	animation.Update(sprite);
	return true;
}
