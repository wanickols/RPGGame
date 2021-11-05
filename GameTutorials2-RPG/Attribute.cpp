#include "stdafx.h"
#include "Attribute.h"
#include "Entity.h"

std::random_device Attribute::seed;
std::default_random_engine Attribute::engine(seed());

//Con //Des
Attribute::Attribute(int level, Entity& owner) :
	level(level), exp(0), attributePoints(3), levelBoostRate(1.f), levelUpdate(true), healthUpdate(true), expUpdate(true), energyUpdate(true),
	Component("attribute", owner)
{
	expnext = 50;
	vitality = 1;
	strength = 1;
	dexterity = 1;
	agility = 1;
	intelligence = 1;
	critChance = .01f;
	critMult = 1.5f;
	range = 30;
	expMult = 1.f;
	updateStats(true);
}

//Utility Functions

int Attribute::calculateExpNext(int level) const
{
	return (50  + (50/3) * static_cast<int>(static_cast<int>(pow(level, 3)) - 6 * static_cast<int>(pow(level, 2)) + (level * 17) - 12));
}

//Main Functions
void Attribute::levelUp()
{
	++level;
	int attributeCap = 50;
	if (level <= attributeCap)
		attributePoints += 2 + (level / 5);
	else
		attributePoints += 2 + (attributeCap / 5);
	vitality += 1;
	strength += 1;
	dexterity += 1;
	agility += 1;
	intelligence += 1;
}

void Attribute::updateStats(const bool reset)
{
	levelUpdate = true;
	healthUpdate = true;
	energyUpdate = true;


	if (level % 10 == 0) {
		switch (level)
		{
		case(10):
			levelBoostRate = 1.1f;
			break;
		case(20):
			levelBoostRate = 1.2f;
			break;
		case(30):
			levelBoostRate = 1.3f;
			break;
		case(40):
			levelBoostRate = 1.4f;
			break;
		case(50):
			levelBoostRate = 1.8f;
			break;
		case(80):
			levelBoostRate = 2.5f;
			break;
		case(100):
			levelBoostRate = 4.f;
			break;
		}
	}
	hpMax     = 70 + (int)(level * levelBoostRate * 10) + (vitality * 10) + (strength * 5) + (intelligence * 5); //base 100
	damageMax = ((4 + strength * 4 + agility * 2) + strength/2); //base 10
	damageMin = ((4 + strength * 4 + agility * 2) + strength / 4); //base 10
	accuracy  = dexterity * 4 + agility * 2; //base 10
	defense   = strength * 2 + agility / 3; // base 2
	energyMax  = 90 + intelligence * 10; //base 100 
	critChance = ((dexterity * 2 + agility * 2 - vitality * 2 + intelligence - strength)/2.f)/100.f; // base 1%
	

		if (reset)
		{
			hp = hpMax;
			energy = energyMax;
		}
}

void Attribute::updateLevel()
{
	while (exp >= expnext) {
		exp -= expnext;
		levelUp();
		randomAssignment();
		updateStats(true);
		expnext = calculateExpNext(level);
	}
}


void Attribute::update(const float& dt, const sf::Vector2f mousePosView)
{
}

void Attribute::randomAssignment()
{
	std::uniform_int_distribution<int> attributeDivider(0, 4);
	while (attributePoints > 0) 
	{
		switch(attributeDivider(engine))
		{
		case(0):
			++vitality;
			break;
		case(1):
			++strength;
			break;
		case(2):
			++dexterity;
			break;
		case(3):
			++agility;
			break;
		case(4):
			++intelligence;
			break;
		default:
			++vitality;
			break;

		}
		--attributePoints;
	}
}

bool Attribute::isDead()
{
	if(hp <= 0)
		return true;
	return false;
}

void Attribute::loseHealth(const int health)
{
	hp -= health;
	healthUpdate = true;
	if (hp < 0)
		hp = 0;
}

void Attribute::addHealth(const int health)
{
	hp += health;
	healthUpdate = true;
	if (hp > hpMax)
		hp = hpMax;
}

void Attribute::loseEnergy(const int energy)
{
	this->energy -= energy;
	energyUpdate = true;
	if (energy < 0)
		this->energy = 0;
}

void Attribute::addEnergy(const int energy)
{
	this->energy += energy;
	energyUpdate = true;
	if (this->energy > energyMax)
		this->energy = energyMax;

}

void Attribute::loseExp(const int xp)
{
	exp -= xp;
	if (exp < 0)
		exp = 0;
}

void Attribute::addExp(int xp)
{
	exp += xp;
	expUpdate = true;
	updateLevel();
}

const std::string Attribute::toStringCharacterTab()
{
	std::stringstream ss;


	ss  
		//header
		<< "Level: " << level << "\n"
		<< "HP: " << hp << "/" << hpMax << "\n"
		<< "Energy: " << energy << "/" << energyMax << "\n"
		<< "Exp: " << exp << "/" << expnext << "\n"

		//Base Attributes
		<< "Attributes" << "\n"
		<< "Vitality: " << vitality << "\n"
		<< "Strength: " << strength << "\n"
		<< "Dexterity: " << dexterity << "\n"
		<< "Agility: " << agility << "\n"
		<< "Intelligence: " << intelligence << "\n"

		<< "Stats" << "\n"
		
		
		<< "Attack: " << damageMax << "\n"
		<< "Crit chance: " << critChance * 100 << "% \n"
		<< "Defense: " << defense << "\n"
		
		<< "Attriubutes Points: " << attributePoints << "\n"
		;

	return ss.str();
}

const int Attribute::getAttributePoints() const
{
	return attributePoints;
}

//Temp
std::string Attribute::debugPrint()
{
	std::stringstream ss;


	ss << "Level: " << level << "\n"
		<< "Exp: " << exp << "\n"
		<< "Exp Next: " << expnext << "\n"
		<< "Exp Multiplier: " << expMult << "\n"
		<< "Attriubutes Points: " << attributePoints << "\n"

		<< "Attributes" << "\n"
		<< "Vitality: " << vitality << "\n"
		<< "Strength: " << strength << "\n"
		<< "Dexterity: " << dexterity << "\n"
		<< "Agility: " << agility << "\n"
		<< "Intelligence: " << intelligence << "\n"

		<< "Stats" << "\n"
		<< "Max Health: " << hpMax << "\n"
		<< "Health: " << hp << "\n"
		<< "Max damage: " << damageMax << "\n"
		<< "Min damage: " << damageMin << "\n"
		<< "Crit chance: " << critChance * 100 << "% \n"
		<< "Crit multiplier: " << critMult << "\n"
		<< "Defense: " << defense << "\n"
		<< "Energy: " << energy << "\n";

	return ss.str();
}
