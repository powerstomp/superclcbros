#ifndef _PHYSICSENGINE_H
#define _PHYSICSENGINE_H

#include "../Utility/Direction.h"
#include "TileMap/TileMap.h"

class Entity;

struct CollisionResult {
	Direction direction = Direction::NONE;
	sf::FloatRect intersection;
	sf::Vector2f overlap;
};

class PhysicsEngine {
private:
	static constexpr double GRAVITY = 1.25;
	static constexpr auto FRICTION = 0.92;
	static constexpr auto AIR_FRICTION = 0.995;
	static constexpr auto TERMINAL_VELOCITY = 25;

	static void ResolveMapCollisionHorizontal(Entity&, const CollisionResult&);
	static void ResolveMapCollisionVertical(Entity&, const CollisionResult&);

	using MapCollisionResolver =
		void(Entity& entity, const CollisionResult& collisionResult);
	static void HandleMapCollision(
		Entity&, const TileMap&, MapCollisionResolver resolver
	);

public:
	void Update(Entity& entity, const TileMap& tileMap);
	void Update(Entity& a, Entity& b);

	static CollisionResult GetCollisionResult(
		const sf::FloatRect& origin, const sf::FloatRect& target
	);
};

#endif
