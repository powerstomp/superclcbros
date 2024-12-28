#include "Goomba.h"

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include "../../Utility/ServiceLocator.h"
#include "../../Utility/TextureManager.h"
#include "../Animation/AnimationManager.h"
#include "../Animation/IdleAnimationHandler.h"

sf::Sprite Goomba::GetSprite() {
	auto sprite = sf::Sprite(
		ServiceLocator<TextureManager>::Get().GetOrLoad("assets/smb_enemies_sheet.png")
	);
	sprite.scale(2.5, 2.5);
	return sprite;
}

Goomba::Goomba(sf::Vector2f position, std::unique_ptr<EntityController> controller)
	: Enemy(GetSprite(), position, 100000, 4, -12, std::move(controller)) {
	AddAnimation(std::make_unique<IdleAnimationHandler>(
		ServiceLocator<AnimationManager>::Get().Get("goomba_moving")
	));
}
