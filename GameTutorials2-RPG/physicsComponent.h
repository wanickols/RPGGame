#pragma once
class PhysicsDevice;

#include "Constants.h"

#include "Component.h"
class physicsComponent :
    public Component
{
public:
    physicsComponent(GAME_PHYSICS physics, std::shared_ptr<PhysicsDevice> p_device, Entity& owner);
    ~physicsComponent();
    void update(const float& dt, const sf::Vector2f mousePosView); 
    const sf::Vector2f getOffset();

    void staticCollisions(Entity* collider);
    void dynamicCollisions(Entity* collider);
    std::shared_ptr<PhysicsDevice> pDevice;
private:
    sf::Vector2f offset;
    GAME_PHYSICS physics;

};

