#ifndef _LUCKYBLOCK_H
#define _LUCKYBLOCK_H

#include "PickupItem.h"

enum class LuckyBlockType {
	COIN,
	MUSHROOM
};

class LuckyBlock : public PickupItem {
private:
	sf::Sprite LoadSprite();

	LuckyBlockType type;

	bool IsAffectedByGravity() const override;
	bool IsAffectedByTiles() const override;

public:
	LuckyBlock(sf::Vector2f position, LuckyBlockType);

	LuckyBlockType GetType() const;
};

#endif
