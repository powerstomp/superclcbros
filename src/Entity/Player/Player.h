#ifndef _PLAYER_H
#define _PLAYER_H

#include "../Entity.h"

enum PlayerModifier {
	NORMAL,
	LARGE,
	FIREPOWER,

	MAX
};

class Enemy;

class Player : public Entity {
protected:
	PlayerModifier modifier = PlayerModifier::NORMAL;

	bool CanUpdateModifier(PlayerModifier) const;
	void OnCollide(Entity&, Direction) override;
	void OnTakeDamage() override;

public:
	Signal<Enemy&> onHitEnemy;

	Player(
		sf::Sprite sprite, sf::Vector2f position, double acceleration, double maxSpeed,
		double jumpVelocity, std::unique_ptr<EntityController> controller
	);

	PlayerModifier GetModifier() const;
	void OnGetModifier(PlayerModifier);
};

#endif
