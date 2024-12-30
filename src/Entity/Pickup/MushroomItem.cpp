#include "MushroomItem.h"

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include "../../Utility/ServiceLocator.h"
#include "../../Utility/TextureManager.h"
#include "../Animation/AnimationManager.h"
#include "../Animation/DeadAnimationHandler.h"
#include "../Animation/IdleAnimationHandler.h"
#include "../Player/Player.h"

sf::Sprite MushroomItem::LoadSprite() {
	auto sprite = sf::Sprite(
		ServiceLocator<TextureManager>::Get().GetOrLoad("assets/pickup_items.png")
	);
	sprite.scale(2.5, 2.5);
	return sprite;
}

MushroomItem::MushroomItem(
	sf::Vector2f position, std::unique_ptr<EntityController> controller
)
	: PickupItem(LoadSprite(), position, std::move(controller)) {
	AddAnimation(std::make_unique<IdleAnimationHandler>(
		ServiceLocator<AnimationManager>::Get().Get("pickup_mushroom")
	));
	AddAnimation(std::make_unique<DeadAnimationHandler>(
		ServiceLocator<AnimationManager>::Get().Get("invisible_1px")
	));
}

void MushroomItem::OnPickup(Player& player) {
	player.OnGetModifier(PlayerModifier::LARGE);
}
