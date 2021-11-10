#pragma once
#include "Component.h"
#include "Movement.h"

class PhysicsDevice;

class bulletC :
    public Component
{
public:
    bulletC(float x, float y, float velX, float velY, sf::Texture& texture, facing direction, Entity& owner);
    void updateAnimation(const float& dt);
    void update(const float& dt, const sf::Vector2f mousePosView);
    const bool getRunning() const;
    void setRunning(const bool running);
    void setDeath(const bool death);
    const sf::Vector2f getStartPosition();
private:
    bool running;
    bool death;
    float xVel;
    float yVel;
    sf::Vector2f startPosition;

};

