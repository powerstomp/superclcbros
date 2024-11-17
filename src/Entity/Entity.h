#ifndef _ENTITY_H
#define _ENTITY_H

#include <string>
#include <memory>



class Entity {
protected:
    float positionX;
    float positionY;
    float width;
    float height;
    bool isActive;

public:
    Entity();
    Entity(float posX, float posY, float width, float height)
        : positionX(posX), positionY(posY), width(width), height(height), isActive(true) {}
    virtual ~Entity() = default;

    virtual void Update() = 0;
    virtual void Render(double deltaTime) = 0;
    virtual void OnCollide(std::shared_ptr<Entity> other) = 0;

    // Getters and setters
    float GetPositionX() const { return positionX; }
    void SetPositionX(float posX) { positionX = posX; }

    float GetPositionY() const { return positionY; }
    void SetPositionY(float posY) { positionY = posY; }

    float GetWidth() const { return width; }
    void SetWidth(float width) { this->width = width; }

    float GetHeight() const { return height; }
    void SetHeight(float height) { this->height = height; }

   
};

#endif
