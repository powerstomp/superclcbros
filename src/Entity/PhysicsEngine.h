#ifndef _PHYSICSENGINE_H
#define _PHYSICSENGINE_H

#include "TileMap/TileMap.h"

class Entity;

enum class Direction {
	NONE = -1,

	LEFT,
	RIGHT,
	UP,
	DOWN,

	MAX
};

struct CollisionResult {
	Direction direction = Direction::NONE;
	sf::FloatRect intersection;
	sf::Vector2f overlap;
};

class PhysicsEngine {
private:
	static constexpr double GRAVITY = 1.25;

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
	void Update(Entity& entity, const TileMap& tileMap);
};

#endif
