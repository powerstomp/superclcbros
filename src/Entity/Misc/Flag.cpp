#include "Flag.h"

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include "../../Utility/ServiceLocator.h"
#include "../../Utility/TextureManager.h"
#include "../Animation/AnimationManager.h"
#include "../Animation/IdleAnimationHandler.h"

sf::Sprite Flag::LoadSprite() {
	auto sprite = sf::Sprite(
		ServiceLocator<TextureManager>::Get().GetOrLoad("assets/misc_sprites.png")
	);
	sprite.scale(2, 2);
	return sprite;
}

Flag::Flag(sf::Vector2f position) : Entity(LoadSprite(), position, 0, 0, 0, nullptr) {
	AddAnimation(std::make_unique<IdleAnimationHandler>(
		ServiceLocator<AnimationManager>::Get().Get("flag")
	));
}

void Flag::OnCollide(Entity& entity, Direction direction) {
}
