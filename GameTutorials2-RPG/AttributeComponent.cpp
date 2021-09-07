#include "stdafx.h"
#include "AttributeComponent.h"

//Con //Des
AttributeComponent::AttributeComponent(int level) :
	level(level), exp(0), attributePoints(3), levelBoostRate(1.f), levelUpdate(true), healthUpdate(true), expUpdate(true), energyUpdate(true)
{
	expnext = 50;
	vitality = 1;
	strength = 1;
	dexterity = 1;
	agility = 1;
	intelligence = 1;
	updateStats(true);
}

//Utility Functions

int AttributeComponent::calculateExpNext(int level) const
{
	return (50  + (50/3) * static_cast<int>(static_cast<int>(pow(level, 3)) - 6 * static_cast<int>(pow(level, 2)) + (level * 17) - 12));
}

//Main Functions
void AttributeComponent::levelUp()
{
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

void AttributeComponent::updateStats(const bool reset)
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
	damageMax = ((5 + strength * 4 + dexterity) + strength/2); //base 10
	damageMin = ((5 + strength * 4 + dexterity) + strength / 4); //base 10
	accuracy  = dexterity * 4 + intelligence * 2; //base 10
	defense   = agility * 2 + agility / 3; // base 2
	energyMax    = 90 + intelligence * 10; //base 100 
	
		if (reset)
		{
			hp = hpMax;
			energy = energyMax;
		}
}

void AttributeComponent::updateLevel()
{
	while (exp >= expnext) {
		exp -= expnext;
		levelUp();
		++level;
		updateStats(true);
		expnext = calculateExpNext(level);
	}
}


void AttributeComponent::update()
{
}

void AttributeComponent::addExp(int xp)
{
	exp += xp;
	expUpdate = true;
	updateLevel();
}

const int AttributeComponent::getAttributePoints() const
{
	return attributePoints;
}

//Temp
std::string AttributeComponent::debugPrint()
{
	std::stringstream ss;


	ss << "Level: " << level << "\n"
		<< "Exp: " << exp << "\n"
		<< "Exp Next: " << expnext << "\n"
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
		<< "Defense: " << defense << "\n"
		<< "Energy: " << energy << "\n";

	return ss.str();
}
