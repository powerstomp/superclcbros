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
#include "Player.h"

sf::Sprite Mario::LoadSprite() {
	auto sprite =
		sf::Sprite(ServiceLocator<TextureManager>::Get().GetOrLoad("assets/mario.png"));
	sprite.scale(2.5, 2.5);
	return sprite;
}

Mario::Mario(sf::Vector2f position, std::unique_ptr<EntityController> controller)
	: Player(LoadSprite(), position, 1.25, 13, -23, std::move(controller)) {
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

	AnimationSet largeSet{.match = [&]() mutable { return modifier == LARGE; }};
	largeSet.animations.push_front(std::make_unique<IdleAnimationHandler>(
		ServiceLocator<AnimationManager>::Get().Get("large_mario_standing")
	));
	largeSet.animations.push_front(std::make_unique<WalkAnimationHandler>(
		ServiceLocator<AnimationManager>::Get().Get("large_mario_running")
	));
	largeSet.animations.push_front(std::make_unique<JumpAnimationHandler>(
		ServiceLocator<AnimationManager>::Get().Get("large_mario_jumping")
	));
	AddAnimationSet(std::move(largeSet));
}
