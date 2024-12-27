#ifndef _SIMPLEAICONTROLLER_H
#define _SIMPLEAICONTROLLER_H

#include "EntityController.h"

class SimpleAIController : public EntityController {
public:
	void Update(Entity& entity) override;
};

#endif
