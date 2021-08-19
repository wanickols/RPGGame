#pragma once
class AttributeComponent
{
public:
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
	
	//Stats
	int hp;
	int hpMax;

	int damageMin;
	int damageMax;

	int accuracy;
	int defense;

	int speed; 

	int energy;
	//Con //Des
	AttributeComponent(int level);

	//Functiomns
	int calculateExpNext(int level);

	void update();

	void updateStats(const bool reset);
	void levelUp();
	void updateLevel();

	std::string debugPrint();
};

