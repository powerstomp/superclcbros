#ifndef _ENTITYCONTROLLER_H
#define _ENTITYCONTROLLER_H

class Entity;

class EntityController {
private:
	EntityController(const EntityController&) = delete;
	EntityController& operator=(const EntityController&) = delete;

	EntityController(EntityController&&) = default;
	EntityController& operator=(EntityController&&) = default;

public:
	EntityController() = default;
	virtual ~EntityController() = default;

	virtual void Update(Entity&) = 0;
};

#endif
