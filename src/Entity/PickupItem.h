#ifndef _PICKUP_ITEM_H
#define _PICKUP_ITEM_H

#include "Entity.h"
#include "Player.h"

class PickupItem : public Entity {
protected:
    int value;
    std::string effect;

public:
    PickupItem();
    PickupItem(Point position, Dimension size, int value, const std::string& effect)
        : Entity(position, size), value(value), effect(effect) {}

    // Override methods
    void Update() override;
    void Render(double deltaTime) override;
    void OnCollide(std::shared_ptr<Entity> other) override;

    // Unique PickupItem methods
    virtual void Collect(std::shared_ptr<Player> collector) = 0;

    // Getters
    int GetValue() const { return value; }
    std::string GetEffect() const { return effect; }
};

class Coin : public PickupItem {
public:
    Coin();
    Coin(Point position, Dimension size, int value)
        : PickupItem(position, size, value, "score") {}

    void Collect(std::shared_ptr<Player> collector) override;
};

class PowerUpItem : public PickupItem {
private:
    int duration; // int or float?

public:
    PowerUpItem();
    PowerUpItem(Point position, Dimension size, int value, const std::string& effect, int duration)
        : PickupItem(position, size, value, effect), duration(duration) {}

    void Collect(std::shared_ptr<Player> collector) override;
    int GetDuration() const { return duration; }

};

#endif

