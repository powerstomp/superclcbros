#ifndef _ENTITYMANAGER_H
#define _ENTITYMANAGER_H

#include <list>
#include <memory>

#include "Entity.h"
#include "TileMap.h"

class EntityManager : public sf::Drawable, public sf::Transformable {
private:
	std::list<std::unique_ptr<Entity>> entities;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

public:
	void AddEntity(std::unique_ptr<Entity>);
	void RemoveEntity(const Entity*);

	void Update(TileMap& tileMap);
};

#endif
