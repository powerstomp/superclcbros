#include "PickupItem.h"

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include "../Player/Player.h"

PickupItem::PickupItem(
	sf::Sprite sprite, sf::Vector2f position, std::unique_ptr<EntityController> controller
)
	: Entity(sprite, position, 100000, 4, -12, std::move(controller)) {
}

void PickupItem::OnPickup(Player& entity) {
}

void PickupItem::OnCollide(Entity& entity, Direction direction) {
	if (auto player = dynamic_cast<Player*>(&entity)) {
		if (!IsDead()) {
			SetDead();
			OnPickup(*player);
			onPickup.Emit(*this);
		}
	}
}
