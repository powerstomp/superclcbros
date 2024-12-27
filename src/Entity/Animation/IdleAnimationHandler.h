#ifndef _IDLEANIMATIONHANDLER_H
#define _IDLEANIMATIONHANDLER_H

#include "AnimationHandler.h"

class IdleAnimationHandler : public AnimationHandler {
public:
	IdleAnimationHandler(Animation animation);
	bool Update(Entity&, sf::Sprite&) override;
};

#endif
