#pragma once
#include "Component.h"
class physicsComponent :
    public Component
{
public:
    physicsComponent(Entity& owner);
    void update(const float& dt, const sf::Vector2f mousePosView);

private:
};

