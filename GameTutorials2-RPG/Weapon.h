#pragma once
#include "ItemComponent.h"
class Weapon :
    public ItemComponent
{
public:
    
    Weapon(int damage_max, int damage_min, int range, int defense, Item& owner, std::string texture_file);

    void update(const float& dt, const sf::Vector2f& mousePosView, const sf::Vector2f& position);
    void render(sf::RenderTarget& target, sf::Shader* shader, sf::Vector2f light_position, const bool show_hitbox);
    
    //accessors
    const int getRange() const;

    void initVaribles() {};
private:
    sf::Sprite sprite;
    sf::Texture texture;
    int damageMin;
    int damageMax;
    int range;
    int defense;
    sf::Clock attackTimer; 
    sf::Int32 attackTimerMax;
};
