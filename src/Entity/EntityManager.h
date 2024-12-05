#ifndef _ENTITYMANAGER_H
#define _ENTITYMANAGER_H

#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>
#include <list>
#include <memory>

#include "Entity.h"
#include "PhysicsEngine.h"
#include "TileMap/TileMap.h"

class EntityManager : public sf::Drawable, public sf::Transformable {
private:
	std::list<std::unique_ptr<Entity>> entities;

	virtual void draw(sf::RenderTarget&, sf::RenderStates) const override;

public:
	void AddEntity(std::unique_ptr<Entity>);
	void RemoveEntity(const Entity*);

	void Update(PhysicsEngine&, TileMap&);
};

#endif
