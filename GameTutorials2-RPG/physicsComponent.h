#pragma once
class PhysicsDevice;


#include "Constants.h"

#include "Component.h"
class physicsComponent :
    public Component
{
public:
    physicsComponent(GAME_PHYSICS physics, Entity& owner);
    ~physicsComponent();
    void update(const float& dt, const sf::Vector2f mousePosView);
    void initialize(std::shared_ptr<PhysicsDevice> p_device);
    const sf::Vector2f getOffset();

    void collisions(Entity* collider);
    std::shared_ptr<PhysicsDevice> pDevice;
private:
    sf::Vector2f offset;
    GAME_PHYSICS physics;

};

