#pragma once
#include "Component.h"
class Item;
class EnemySpawner;
class EnemyStats : public Component
{
public:
	EnemyStats(std::string name, int expWorth, Item& dropItem, EnemySpawner& origin, Entity* owner);
	void update(const float& dt, const sf::Vector2f mousePosView);
private:
	std::unique_ptr<EnemySpawner> Origin;
	std::unique_ptr<Item> dropItem; //Item Dropped when enemy dies;
	int expWorth; //Exp given when enemy dies
	std::string name;
};


