#include "stdafx.h"
#include "Combat.h"
#include "Entity.h"
#include "Attribute.h"
#include "EnemyData.h"
#include "enemyGui.h"
#include "physicsComponent.h"
#include "PhysicsDevice.h"
#include "Movement.h"
#include "enemyAi.h"

std::random_device Combat::seed;
std::default_random_engine Combat::engine(seed());

Combat::Combat(Entity& owner)
	: Component("Combat", owner)
{
	attribute = owner.getComponent<Attribute>();
}

int Combat::attack()
{

	int damage = 0;
	float mean = (attribute->damageMin + (attribute->damageMax - attribute->damageMin) / 2);

	std::normal_distribution<float> damageRange(mean, 3.f);

	float crit = attribute->critChance;
	if (crit > 1.f)
		crit = 1.f;
	else if (crit < 0.f)
		crit = 0.f;

	std::bernoulli_distribution critChance(crit);

	damage = damageRange(engine);

	if (critChance(engine)) //critchance
		damage = damage * attribute->critMult; //crit multiple

	/*if (owner.getComponent<EnemyData>() != nullptr)
		std::cout << owner.getComponent<EnemyData>()->getEnemyName() << " attacked!" << "\n";
	else
		std::cout << "Player attacked!" << "\n";*/

	return damage;
}

int Combat::defend(Entity& attacker)
{
	int damage = attacker.getComponent<Combat>()->attack();
	
	//Damage Calculation
	damage -= attribute->defense; //minus attack by defense
	if(damage <= 0)
	{
		damage = 2;
	}
	
	//Gui Showing
	if (owner.getComponent<enemyGui>() != nullptr)
	{
		owner.getComponent<enemyGui>()->setHidden(false);
	}

	if (owner.getComponent<enemyAi>() != nullptr) {
		
		float stun_chance = attacker.getComponent<Attribute>()->stunChance;
		stun_chance -= owner.getComponent<Attribute>()->stunResistance;

		if (stun_chance < 0.f)
			stun_chance = 0;
		else if (stun_chance > 1.f)
			stun_chance = 1.f;

		std::bernoulli_distribution stunChance(stun_chance);
		if (stunChance(engine))
		{
			owner.getComponent<enemyAi>()->setStunned(true);
		}
	}

	//lose health
	attribute->loseHealth(damage);

	//Physics
	b2Body* body = owner.getComponent<physicsComponent>()->pDevice->findBody(owner);
	b2Vec2 velocity = body->GetLinearVelocity();
	float force = 24.f * damage;
	if (force > 1000)
		force = 1000;
		switch (owner.getComponent<Movement>()->getDirection()) 
		{
		case(facing::LEFT):
			velocity.x = -force;
			break;
		case(facing::RIGHT):
			velocity.x = force;
			break;
		case(facing::UP):
			velocity.y = -force;
			break;
		case(facing::DOWN):
			velocity.y = force;
			break;
		};
	
	body->ApplyLinearImpulseToCenter(b2Vec2({-velocity.x, -velocity.y}), true);

	return damage;
}

int Combat::expHandler(int deathExp, int deathLevel)
{
	int xp = deathExp;
	xp = xp * owner.getComponent<Attribute>()->expMult;
	
	float levelBasedMult = 1.f + (deathLevel - owner.getComponent<Attribute>()->level)/10.f;
	if (levelBasedMult <= .4f)
		levelBasedMult = .4f;

	xp = (int)(xp * levelBasedMult);
	owner.getComponent<Attribute>()->addExp(xp);
	return xp;
}

void Combat::update(const float& dt, const sf::Vector2f mousePosView)
{
}
