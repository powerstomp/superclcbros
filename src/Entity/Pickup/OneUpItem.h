#ifndef _ONEUPITEM_H
#define _ONEUPITEM_H

#include "PickupItem.h"

class OneUpItem : public PickupItem {
private:
	sf::Sprite LoadSprite();

public:
	OneUpItem(sf::Vector2f position, std::unique_ptr<EntityController> controller);
};

#endif
