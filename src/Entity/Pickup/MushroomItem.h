#ifndef _MUSHROOMITEM_H
#define _MUSHROOMITEM_H

#include "PickupItem.h"

class MushroomItem : public PickupItem {
private:
	sf::Sprite LoadSprite();
	void OnPickup(Player& entity) override;

public:
	MushroomItem(sf::Vector2f position, std::unique_ptr<EntityController> controller);
};

#endif
