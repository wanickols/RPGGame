#include "stdafx.h"
#include "Combat.h"
#include "Entity.h"
#include "Attribute.h"
#include "EnemyData.h"
#include "enemyGui.h"

std::random_device Combat::seed;
std::default_random_engine Combat::engine(seed());

Combat::Combat(Entity* owner)
	: Component("Combat", owner)
{

}

int Combat::attack()
{

	int damage = 0;
	float mean = (owner->getComponent<Attribute>()->damageMin + (owner->getComponent<Attribute>()->damageMax - owner->getComponent<Attribute>()->damageMin) / 2);

	std::normal_distribution<float> damageRange(mean, 3.f);

	float crit = owner->getComponent<Attribute>()->critChance;
	if (crit > 1.f)
		crit = 1.f;
	else if (crit < 0.f)
		crit = 0.f;

	std::bernoulli_distribution critChance(crit);

	damage = damageRange(engine);

	if (critChance(engine)) //critchance
		damage = damage * owner->getComponent<Attribute>()->critMult; //crit multiple

	/*if (owner->getComponent<EnemyData>() != nullptr)
		std::cout << owner->getComponent<EnemyData>()->getEnemyName() << " attacked!" << "\n";
	else
		std::cout << "Player attacked!" << "\n";*/

	return damage;
}

void Combat::defend(int damage)
{
	
	damage -= owner->getComponent<Attribute>()->defense; //minus attack by defense
	if(damage <= 0)
	{
		damage = 2;
	}
	
	if (owner->getComponent<enemyGui>() != nullptr)
	{
		owner->getComponent<enemyGui>()->setHidden(false);
	}
	//std::cout << owner->getComponent<EnemyData>()->getEnemyName() << " defended!" << "\n";
	//else 
		//std::cout << "Player defended!" << "\n";
	owner->getComponent<Attribute>()->loseHealth(damage);
}

int Combat::expHandler(int deathExp, int deathLevel)
{
	int xp = deathExp;
	xp = xp * owner->getComponent<Attribute>()->expMult;
	
	float levelBasedMult = 1.f + (deathLevel - owner->getComponent<Attribute>()->level)/10.f;
	if (levelBasedMult <= .4f)
		levelBasedMult = .4f;

	xp = (int)(xp * levelBasedMult);
	owner->getComponent<Attribute>()->addExp(xp);
	return xp;
}

void Combat::update(const float& dt, const sf::Vector2f mousePosView)
{
}
