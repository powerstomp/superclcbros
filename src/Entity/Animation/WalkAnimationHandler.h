#ifndef _WALKANIMATIONHANDLER_H
#define _WALKANIMATIONHANDLER_H

#include "AnimationHandler.h"

class WalkAnimationHandler : public AnimationHandler {
public:
	WalkAnimationHandler(Animation animation);
	bool Update(Entity&, sf::Sprite&) override;
};

#endif
