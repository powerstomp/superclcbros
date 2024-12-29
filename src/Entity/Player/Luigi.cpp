#include "Luigi.h"

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include "../../Utility/ServiceLocator.h"
#include "../../Utility/TextureManager.h"
#include "../Animation/AnimationManager.h"
#include "../Animation/DeadAnimationHandler.h"
#include "../Animation/IdleAnimationHandler.h"
#include "../Animation/JumpAnimationHandler.h"
#include "../Animation/WalkAnimationHandler.h"

sf::Sprite Luigi::GetSprite() {
	auto sprite =
		sf::Sprite(ServiceLocator<TextureManager>::Get().GetOrLoad("assets/luigi.png"));
	sprite.scale(2.5, 2.5);
	return sprite;
}

Luigi::Luigi(sf::Vector2f position, std::unique_ptr<EntityController> controller)
	: Player(GetSprite(), position, 1, 10, -26, std::move(controller)) {
	AddAnimation(std::make_unique<IdleAnimationHandler>(
		ServiceLocator<AnimationManager>::Get().Get("luigi_standing")
	));
	AddAnimation(std::make_unique<WalkAnimationHandler>(
		ServiceLocator<AnimationManager>::Get().Get("luigi_running")
	));
	AddAnimation(std::make_unique<JumpAnimationHandler>(
		ServiceLocator<AnimationManager>::Get().Get("luigi_jumping")
	));
	AddAnimation(std::make_unique<DeadAnimationHandler>(
		ServiceLocator<AnimationManager>::Get().Get("luigi_death")
	));
}
