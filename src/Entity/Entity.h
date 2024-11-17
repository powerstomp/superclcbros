#ifndef _ENTITY_H
#define _ENTITY_H

#include <string>
#include <memory>

// Basic 2D point structure
struct Point {
    float x, y;
};

// Basic 2D size structure
struct Dimension {
    float width, height;
};

struct Vector {
    float x, y;
};

class Entity {
protected:
    Point position;
    Dimension size;
    Vector velocity;
    bool isActive;

public:
    Entity();
    Entity(Point position, Dimension size)
        : position(position), size(size), velocity({0, 0}), isActive(true) {}
    virtual ~Entity() = default;

    virtual void Update() = 0;
    virtual void Render(double deltaTime) = 0;
    virtual void OnCollide(std::shared_ptr<Entity> other) = 0;

    // Getters and setters
    Point GetPosition() const { return position; }
    void SetPosition(Point position) { this->position = position; }

    Dimension GetSize() const { return size; }
    void SetSize(Dimension size) { this->size = size; }

    Vector GetVelocity() const { return velocity; }
    void SetVelocity(Vector velocity) { this->velocity = velocity; }
};

#endif
