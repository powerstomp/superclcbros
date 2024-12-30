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

	bool touchedFlag = false;
	bool CanMove() const override;

	bool CanUpdateModifier(PlayerModifier) const;
	void OnCollide(Entity&, Direction) override;
	bool OnTakeDamage() override;

public:
	Signal<Enemy&> onHitEnemy;
	Signal<> onTouchFlag;
	Signal<PlayerModifier> onGetModifier;

	Player(
		sf::Sprite sprite, sf::Vector2f position, double acceleration, double maxSpeed,
		double jumpVelocity, std::unique_ptr<EntityController> controller
	);

	bool Kill() override;
	PlayerModifier GetModifier() const;
	void OnGetModifier(PlayerModifier);
};

#endif
