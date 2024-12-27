#ifndef _PLAYERCONTROLLER_H
#define _PLAYERCONTROLLER_H

#include "EntityController.h"

class PlayerController : public EntityController {
public:
	void Update(Entity& entity) override;
};

#endif
