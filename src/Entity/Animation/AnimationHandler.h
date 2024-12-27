#ifndef _ANIMATIONHANDLER_H
#define _ANIMATIONHANDLER_H

#include "Animation.h"

class Entity;

class AnimationHandler {
private:
	AnimationHandler(const AnimationHandler&) = delete;
	AnimationHandler& operator=(const AnimationHandler&) = delete;

	AnimationHandler(AnimationHandler&&) = default;
	AnimationHandler& operator=(AnimationHandler&&) = default;

protected:
	Animation animation;

public:
	AnimationHandler(Animation animation);
	virtual ~AnimationHandler() = default;

	virtual bool Update(Entity&, sf::Sprite&) = 0;
};

#endif
