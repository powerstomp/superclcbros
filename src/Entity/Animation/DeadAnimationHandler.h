#ifndef _DEADANIMATIONHANDLER_H
#define _DEADANIMATIONHANDLER_H

#include "AnimationHandler.h"

class DeadAnimationHandler : public AnimationHandler {
public:
	DeadAnimationHandler(Animation animation);
	bool Update(Entity&, sf::Sprite&) override;
};

#endif
