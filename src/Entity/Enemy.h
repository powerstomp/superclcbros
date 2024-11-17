#ifndef _ENEMY_H
#define _ENEMY_H

#include "Entity.h"
#include "Player.h"

class Enemy : public Entity {
protected:
    int damage;
    float speed;
    bool isAggressive;

public:
    Enemy();
    Enemy(Point position, Dimension size, int damage, float speed, bool isAggressive)
        : Entity(position, size), damage(damage), speed(speed), isAggressive(isAggressive) {}

    virtual void Behavior(std::shared_ptr<Player> player) = 0;
    void attack(std::shared_ptr<Player> player);
    

    // Getters
    int GetDamage() const { return damage; }
    float GetSpeed() const { return speed; }
};

class Goomba : public Enemy {
public:
    Goomba();
    Goomba(Point position, Dimension size, int damage, float speed, bool isAggressive)
        : Enemy(position, size, damage, speed, isAggressive) {}

    void Behavior(std::shared_ptr<Player> player) override;
};

class Koopa : public Enemy {
public:
    Koopa();
    Koopa(Point position, Dimension size, int damage, float speed, bool isAggressive)
        : Enemy(position, size, damage, speed, isAggressive) {}

    void Behavior(std::shared_ptr<Player> player) override;
};

#endif