#include "stdafx.h"
#include "EnemyData.h"
#include "Item.h"
#include "Entity.h"
#include "Attribute.h"

EnemyData::EnemyData(std::string name, EnemyPowerLevel enemy_power_level, float exp_mult, float vitality_multiplier, float strength_multiplier, float dexterity_multiplier, float agility_multiplier, float intelligence_multiplier, Item* dropItem, std::shared_ptr<EnemySpawner> origin, Entity* owner)
	: Component("enemyData", owner)
{
	Origin = origin;
	if(dropItem != nullptr)
		this->dropItem = std::make_unique<Item>(*dropItem);

	this->enemyName = name;
	expWorth = 100 * exp_mult * (owner->getComponent<Attribute>()->level/2.5);

	enemyPowerLevel = enemy_power_level;
	//Species strength Multipliers
	owner->getComponent<Attribute>()->vitality * vitality_multiplier * enemyPowerLevel;
	owner->getComponent<Attribute>()->strength * strength_multiplier * enemyPowerLevel;
	owner->getComponent<Attribute>()->agility* agility_multiplier;
	owner->getComponent<Attribute>()->dexterity * dexterity_multiplier;
	owner->getComponent<Attribute>()->intelligence * intelligence_multiplier;
}

const std::string EnemyData::getEnemyName()
{
	return enemyName;
}

std::shared_ptr<EnemySpawner> EnemyData::getOrigin()
{
	return Origin;
}

void EnemyData::reduceEnemySpawned()
{
	this->Origin->reduceTotalSpawned();
}
