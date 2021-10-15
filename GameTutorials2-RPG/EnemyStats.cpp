#include "stdafx.h"
#include "EnemyStats.h"
#include "EnemySpawner.h"
#include "Item.h"
#include "Entity.h"

EnemyStats::EnemyStats(std::string name, int exp_worth, Item& drop_item, EnemySpawner &origin, Entity* owner)
	: Component("enemyStats", owner)
{
	
}
