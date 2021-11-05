#pragma once
#include "Component.h"

class Item;
class Inventory;
class ItemLibrary;

class ItemComp :
    public Component
{
public:
    void initInventory();

    ItemComp(Entity& owner);
    void initLibrary(std::shared_ptr<ItemLibrary> item_lib);

    void update(const float& dt, const sf::Vector2f mousePosView) {};

    bool addItem(std::string itemName, bool setActive = false);
    bool dropItem(int index);
   
    std::shared_ptr<ItemLibrary> itemLib;
    std::vector< std::shared_ptr<Item>> weapons;
    std::shared_ptr <Item> activeRune;
    std::shared_ptr<Inventory> inventory;
private:

};

