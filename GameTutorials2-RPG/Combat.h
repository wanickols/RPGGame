#pragma once
#include "Component.h"
class Combat :
    public Component
{
public:
    Combat(Entity& owner);

    int attack();
    void defend(int damage);

    int expHandler(int deathExp, int deathLevel);

    void update(const float& dt, const sf::Vector2f mousePosView);
    void render(sf::RenderTarget& target, sf::Shader* shader, sf::Vector2f light_position, const bool show_hitbox) {};

    //random devices for random gen
    static std::random_device seed;
    static std::default_random_engine engine;
private:

};

