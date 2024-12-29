#include "Piranha.h"

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include "../../Utility/ServiceLocator.h"
#include "../../Utility/TextureManager.h"
#include "../Animation/AnimationManager.h"
#include "../Animation/IdleAnimationHandler.h"
#include "../Player/Player.h"

sf::Sprite Piranha::GetSprite() {
	auto sprite = sf::Sprite(
		ServiceLocator<TextureManager>::Get().GetOrLoad("assets/smb_enemies_sheet.png")
	);
	sprite.scale(2.5, 2.5);
	return sprite;
}

Piranha::Piranha(sf::Vector2f position) : Enemy(GetSprite(), position, 0, 0, 0, nullptr) {
	AddAnimation(std::make_unique<IdleAnimationHandler>(
		ServiceLocator<AnimationManager>::Get().Get("piranha")
	));
}

bool Piranha::OnTakeDamage() {
	return false;
}

void Piranha::OnCollide(Entity& entity, Direction direction) {
	if (auto player = dynamic_cast<Player*>(&entity))
		player->TakeDamage();
}
