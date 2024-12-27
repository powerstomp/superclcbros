#include "IdleAnimationHandler.h"

#include <SFML/Graphics/Sprite.hpp>

#include "../Entity.h"
#include "AnimationHandler.h"

IdleAnimationHandler::IdleAnimationHandler(Animation animation)
	: AnimationHandler(animation) {
}

bool IdleAnimationHandler::Update(Entity& entity, sf::Sprite& sprite) {
	animation.Update(sprite);
	return true;
}
