#include "stdafx.h"
#include "EnemyData.h"
#include "Item.h"
#include "Entity.h"

EnemyData::EnemyData(std::string name, int exp_worth, Item* drop_item, EnemySpawner& origin, Entity* owner)
	: Component("enemyData", owner)
{
	Origin = std::make_unique<EnemySpawner>(origin);
	dropItem = nullptr;
	this->name = name;
	expWorth = exp_worth;
}
