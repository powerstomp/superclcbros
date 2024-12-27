#ifndef _JUMPANIMATIONHANDLER_H
#define _JUMPANIMATIONHANDLER_H

#include "AnimationHandler.h"

class JumpAnimationHandler : public AnimationHandler {
public:
	JumpAnimationHandler(Animation animation);
	bool Update(Entity&, sf::Sprite&) override;
};

#endif
