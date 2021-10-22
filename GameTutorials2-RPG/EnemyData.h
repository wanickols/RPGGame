#pragma once
#include "Component.h"
#include "EnemySpawner.h"
#include "Item.h"

class EnemyData :
    public Component
{
public:
    EnemyData(std::string name, int expWorth, Item* dropItem, EnemySpawner& origin, Entity* owner);
	void update(const float& dt, const sf::Vector2f mousePosView) {};
private:
	std::unique_ptr<EnemySpawner> Origin;
	std::unique_ptr<Item> dropItem; //Item Dropped when enemy dies;
	int expWorth; //Exp given when enemy dies
	std::string name;
};

