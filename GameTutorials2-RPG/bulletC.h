#pragma once
#include "Component.h"

class PhysicsDevice;

class bulletC :
    public Component
{
public:
    bulletC(float x, float y, float velX, float velY, sf::Texture& texture, const unsigned short state, Entity& owner);
    void updateAnimation(const float& dt);
    void initialize(std::shared_ptr<PhysicsDevice> p_device);
    void update(const float& dt, const sf::Vector2f mousePosView);
    const bool getRunning() const;
private:
    bool running;
    float xVel;
    float yVel;

};

