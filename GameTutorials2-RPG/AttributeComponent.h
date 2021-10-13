#pragma once
#include "Component.h"

class AttributeComponent : public Component
{
public:
	
 //Variables 
	//Leveling
	 int level;
	 float levelBoostRate;
	 int exp;
	 int expnext;
	 int attributePoints;

	//Attributes
	 int vitality;
	 int strength;
	 int dexterity;
	 int agility;
	 int intelligence;
	//

	//Stats
	 int hp;
	 int hpMax;
	
	 int damageMin;
  	 int damageMax;

     int accuracy;
 	 int defense;

	 int speed;

	 int energy;
	 int energyMax;
	//
	 //Update Booleans (for listner functions so they don't don't constant update)
	 bool levelUpdate;
	 bool healthUpdate;
	 bool expUpdate;
	 bool energyUpdate;

	
	//Con 
	AttributeComponent(int level, Entity* owner);

	//Utility Functions
	int calculateExpNext(int level) const;
	
	//Main Functions
	void levelUp();
	void updateStats(const bool reset);
	void updateLevel();
	void update(const float& dt, const sf::Vector2f mousePosView);

	//Attribute Functions
	void loseHealth(const int health);
	void addHealth(const int health);
	void loseEnergy(const int energy);
	void addEnergy(const int energy);
	void loseExp(const int exp);
	void addExp(int xp);

	//Accessor
	const int getAttributePoints() const;

	//Temp
	std::string debugPrint();
};

