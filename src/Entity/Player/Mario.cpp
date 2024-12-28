#include "Mario.h"

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include "../../Utility/ServiceLocator.h"
#include "../../Utility/TextureManager.h"
#include "../Animation/AnimationManager.h"
#include "../Animation/DeadAnimationHandler.h"
#include "../Animation/IdleAnimationHandler.h"
#include "../Animation/JumpAnimationHandler.h"
#include "../Animation/WalkAnimationHandler.h"

sf::Sprite Mario::GetSprite() {
	auto sprite =
		sf::Sprite(ServiceLocator<TextureManager>::Get().GetOrLoad("assets/mario.png"));
	sprite.scale(2.5, 2.5);
	return sprite;
}

Mario::Mario(sf::Vector2f position, std::unique_ptr<EntityController> controller)
	: Player(GetSprite(), position, 1, 10, -23, std::move(controller)) {
	AddAnimation(std::make_unique<IdleAnimationHandler>(
		ServiceLocator<AnimationManager>::Get().Get("mario_standing")
	));
	AddAnimation(std::make_unique<WalkAnimationHandler>(
		ServiceLocator<AnimationManager>::Get().Get("mario_running")
	));
	AddAnimation(std::make_unique<JumpAnimationHandler>(
		ServiceLocator<AnimationManager>::Get().Get("mario_jumping")
	));
	AddAnimation(std::make_unique<DeadAnimationHandler>(
		ServiceLocator<AnimationManager>::Get().Get("mario_death")
	));
}
