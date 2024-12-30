#include "LuckyBlock.h"

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include "../../Utility/ServiceLocator.h"
#include "../../Utility/TextureManager.h"
#include "../Animation/AnimationManager.h"
#include "../Animation/DeadAnimationHandler.h"
#include "../Animation/IdleAnimationHandler.h"

sf::Sprite LuckyBlock::LoadSprite() {
	auto sprite = sf::Sprite(
		ServiceLocator<TextureManager>::Get().GetOrLoad("assets/pickup_items.png")
	);
	auto scale = static_cast<float>(TILE_SIZE) / 16;
	sprite.scale(scale, scale);
	return sprite;
}

LuckyBlock::LuckyBlock(sf::Vector2f position, LuckyBlockType type)
	: PickupItem(LoadSprite(), position, nullptr), type(type) {
	AddAnimation(std::make_unique<IdleAnimationHandler>(
		ServiceLocator<AnimationManager>::Get().Get("pickup_block")
	));
	AddAnimation(std::make_unique<DeadAnimationHandler>(
		ServiceLocator<AnimationManager>::Get().Get("invisible_1px")
	));
}

bool LuckyBlock::IsAffectedByGravity() const {
	return false;
}
bool LuckyBlock::IsAffectedByTiles() const {
	return false;
}

LuckyBlockType LuckyBlock::GetType() const {
	return type;
}
