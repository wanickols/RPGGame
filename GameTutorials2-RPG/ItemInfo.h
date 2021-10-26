#pragma once
#include "ItemComponent.h"

enum ItemRarity {Unique = 0, Common, Uncommon, Rare, Epic, Legendery, MYTHICAL};

class ItemInfo :
    public ItemComponent
{
public:
    //Constructors
    ItemInfo(int value, int level, std::string name, std::string desc, short rarity, short item_class, Item& owner);
  
    //Accessors
    int getValue() const;
    const std::string getName() const;
    const std::string getDescription() const;
    const ItemRarity getRarity() const;
    const short getRarityS() const;
    const short getClass() const;
    const int getLevel() const;

    void update(const float& dt, const sf::Vector2f& mousePosView, const sf::Vector2f& position) {};
    void render(sf::RenderTarget& target, sf::Shader* shader = NULL, sf::Vector2f light_position = sf::Vector2f(), const bool show_hitbox = false) {};

    //Setters
    void setValue(int value);
    void calculateValue();
    void setName(std::string& name);
    void setDescription(std::string& desc);
    void setClass(short item_class);
    void setLevel(const int level);


    void initVaribles() {};
private:
    int value;
    int level;
    std::string name;
    std::string description;
    short itemClass;
    short rarity;
};

