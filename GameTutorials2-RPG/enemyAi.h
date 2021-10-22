#pragma once
#include "Component.h"
class enemyAi :
    public Component
{
public:
    enemyAi(Entity* owner);
    void update(const float& dt, const sf::Vector2f mousePosView);
    void render(sf::RenderTarget& target, sf::Shader* shader, sf::Vector2f light_position, const bool show_hitbox);
private:

};
