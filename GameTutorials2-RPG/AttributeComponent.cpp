#include "stdafx.h"
#include "AttributeComponent.h"

//Con //Des
AttributeComponent::AttributeComponent(int level) :
	level(level), exp(0), attributePoints(3), levelBoostRate(1.f), levelUpdate(true), healthUpdate(true), expUpdate(true)
{
	this->expnext = 50;
	this->vitality = 1;
	this->strength = 1;
	this->dexterity = 1;
	this->agility = 1;
	this->intelligence = 1;
	updateStats(true);
}

//Utility Functions

int AttributeComponent::calculateExpNext(int level) const
{
	return (50  + (50/3) * (int)(pow(this->level, 3) - 6 * pow(this->level, 2) + (this->level*17) - 12));
}

//Main Functions
void AttributeComponent::levelUp()
{
	int attributeCap = 50;
	if (level <= attributeCap)
		this->attributePoints += 2 + (level / 5);
	else
		this->attributePoints += 2 + (attributeCap / 5);
	this->vitality += 1;
	this->strength += 1;
	this->dexterity += 1;
	this->agility += 1;
	this->intelligence += 1;
}

void AttributeComponent::updateStats(const bool reset)
{
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
	this->hpMax     = 70 + (int)(level * levelBoostRate * 10) + (vitality * 10) + (strength * 5) + (intelligence * 5); //base 100
	this->damageMax = ((5 + this->strength * 4 + dexterity) + this->strength/2); //base 10
	this->damageMin = ((5 + this->strength * 4 + dexterity) + this->strength / 4); //base 10
	this->accuracy  = this->dexterity * 4 + intelligence * 2; //base 10
	this->defense   = this->agility * 2 + this->agility / 3; // base 2
	this->energy    = 90 + this->intelligence * 10; //base 100 
	
		if (reset)
		{
			this->hp = this->hpMax;
		}
}

void AttributeComponent::updateLevel()
{
	while (this->exp >= this->expnext) {
		levelUpdate = true;
		healthUpdate = true;
		this->exp -= this->expnext;
		this->levelUp();
		++this->level;
		this->updateStats(true);
		this->expnext = calculateExpNext(this->level);
	}
}


void AttributeComponent::update()
{
}

void AttributeComponent::addExp(int xp)
{
	this->exp += xp;
	this->expUpdate = true;
	this->updateLevel();
}

const int AttributeComponent::getAttributePoints() const
{
	return this->attributePoints;
}

//Temp
std::string AttributeComponent::debugPrint()
{
	std::stringstream ss;


	ss << "Level: " << this->level << "\n"
		<< "Exp: " << this->exp << "\n"
		<< "Exp Next: " << this->expnext << "\n"
		<< "Attriubutes Points: " << this->attributePoints << "\n"

		<< "Attributes" << "\n"
		<< "Vitality: " << this->vitality << "\n"
		<< "Strength: " << this->strength << "\n"
		<< "Dexterity: " << this->dexterity << "\n"
		<< "Agility: " << this->agility << "\n"
		<< "Intelligence: " << this->intelligence << "\n"

		<< "Stats" << "\n"
		<< "Max Health: " << this->hpMax << "\n"
		<< "Health: " << this->hp << "\n"
		<< "Max damage: " << this->damageMax << "\n"
		<< "Min damage: " << this->damageMin << "\n"
		<< "Defense: " << this->defense << "\n"
		<< "Energy: " << this->energy << "\n";

	return ss.str();
}
