#pragma once
class AttributeComponent
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
	//
 //Variables
	
	//Con 
	AttributeComponent(int level);

	//Utility Functions
	int calculateExpNext(int level) const;
	
	//Main Functions
	void levelUp();
	void updateStats(const bool reset);
	void updateLevel();
	void update();

	void addExp(int xp);

	//Accessor
	const int getAttributePoints() const;

	//Temp
	std::string debugPrint();
};

