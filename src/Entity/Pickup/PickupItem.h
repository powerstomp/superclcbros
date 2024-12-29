#ifndef _PICKUPITEM_H
#define _PICKUPITEM_H

#include "../Entity.h"

class PickupItem : public Entity {
protected:
	void OnCollide(Entity&, Direction) override;

public:
	Signal<> onPickup;
	PickupItem(
		sf::Sprite sprite, sf::Vector2f position,
		std::unique_ptr<EntityController> controller
	);
};

#endif
