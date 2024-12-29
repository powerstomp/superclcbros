#ifndef _COINITEM_H
#define _COINITEM_H

#include "PickupItem.h"

class CoinItem : public PickupItem {
private:
	sf::Sprite LoadSprite();

protected:
	bool CanMove() const override;
	bool IsAffectedByGravity() const override;

public:
	CoinItem(sf::Vector2f position, std::unique_ptr<EntityController> controller);
};

#endif
