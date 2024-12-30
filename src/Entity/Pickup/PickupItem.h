#ifndef _PICKUPITEM_H
#define _PICKUPITEM_H

#include "../Entity.h"

class Player;

class PickupItem : public Entity {
protected:
	void OnCollide(Entity&, Direction) override;
	virtual void OnPickup(Player& entity);

public:
	Signal<PickupItem&> onPickup;
	PickupItem(
		sf::Sprite sprite, sf::Vector2f position,
		std::unique_ptr<EntityController> controller
	);
};

#endif
