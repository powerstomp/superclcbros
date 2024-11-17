#ifndef _PLAYER_H
#define _PLAYER_H

#include "Entity.h"

class Player : public Entity {
private:
    int health;
    int lives;
    std::string state; // "normal", "invincible", "super", etc.

public:
    Player();
    Player(Point position, Dimension size, int health, int lives)
        : Entity(position, size), health(health), lives(lives), state("normal") {}

    // Override methods
    void Update() override;
    void Render(double deltaTime) override;
    void OnCollide(std::shared_ptr<Entity> other) override;

    // Unique Player methods
    void Move(Vector direction);
    void Jump();
    void TakeDamage(int damage);
    


    // Getters and setters
    int GetHealth() const { return health; }
    void SetHealth(int health) { this->health = health; }

    int GetLives() const { return lives; }
    void SetLives(int lives) { this->lives = lives; }

    std::string GetState() const { return state; }
    void SetState(const std::string state) { this->state = state; }  
};

#endif
    
