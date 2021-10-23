#pragma once
#include "Component.h"

class Item;
class Inventory;

class ItemComp :
    public Component
{
public:
    void initInventory();

    ItemComp(Entity* owner);
    void update(const float& dt, const sf::Vector2f mousePosView) {};

    bool addItem();

    std::vector< std::shared_ptr<Item>> weapons;
    std::shared_ptr <Item> activeRune;
    std::shared_ptr<Inventory> inventory;
private:

};

