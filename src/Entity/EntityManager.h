#ifndef _ENTITYMANAGER_H
#define _ENTITYMANAGER_H

#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>
#include <list>
#include <memory>

#include "Entity.h"
#include "TileMap.h"

struct CollisionResult {
	Direction direction = Direction::NONE;
	sf::FloatRect intersection;
	sf::Vector2f overlap;
};

class EntityManager : public sf::Drawable, public sf::Transformable {
private:
	std::list<std::unique_ptr<Entity>> entities;

	virtual void draw(sf::RenderTarget&, sf::RenderStates) const override;

	static CollisionResult GetCollisionResult(
		const sf::FloatRect& origin, const sf::FloatRect& target
	);
	static void ResolveMapCollisionHorizontal(Entity&, const CollisionResult&);
	static void ResolveMapCollisionVertical(Entity&, const CollisionResult&);

	using MapCollisionResolver =
		void(Entity& entity, const CollisionResult& collisionResult);
	static void HandleMapCollision(
		Entity&, const TileMap&, MapCollisionResolver resolver
	);

public:
	void AddEntity(std::unique_ptr<Entity>);
	void RemoveEntity(const Entity*);

	void Update(TileMap&);
};

#endif
