#pragma once
#include "Component.h"
#include "EnemySpawner.h"
#include "Item.h"

enum EnemyPowerLevel{ NORMAL = 1, ELITE, BOSS};

class EnemyData :
    public Component
{
public:
    EnemyData(std::string enemyName, EnemyPowerLevel enemyPowerLevel, float exp_mult, float vitality_multiplier, float strength_multiplier, float dexterity_multiplier, float agility_multiplier, float intellgence_multiplier, Item* dropItem, EnemySpawner& origin, Entity* owner);
	void update(const float& dt, const sf::Vector2f mousePosView) {};

	const std::string getEnemyName();
	int expWorth; //Exp given when enemy dies

private:
	std::unique_ptr<EnemySpawner> Origin;
	std::unique_ptr<Item> dropItem; //Item Dropped when enemy dies;
	std::string enemyName;
	short enemyPowerLevel;
};

