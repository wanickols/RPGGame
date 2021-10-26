#pragma once
#include "ItemComponent.h"
enum ItemRarity;

class Weapon :
    public ItemComponent
{
public:
    
    Weapon(int damage,int level, int levelMax, int range, int defense, Item& owner, std::string texture_file);

    void update(const float& dt, const sf::Vector2f& mousePosView, const sf::Vector2f& position);
    void render(sf::RenderTarget& target, sf::Shader* shader, sf::Vector2f light_position, const bool show_hitbox);
    
    void generateLevel(ItemRarity rarity);

    //accessors
    const int getRange() const;
    const bool getAttackTimer();

    void initVaribles() {};
private:

    sf::Sprite sprite;
    sf::Texture texture;
    int damage;
    int range;
    int defense;
    int levelMax;
    int level;
    sf::Clock attackTimer; 
    sf::Int32 attackTimerMax;

    static std::random_device seed;
    static std::default_random_engine engine;
};

