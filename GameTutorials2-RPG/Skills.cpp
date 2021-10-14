#include "stdafx.h"
#include "Skills.h"

Skills::Skills(Entity* owner)
	: Component("skill", owner)

{
	skills["Endurance"];
	skills["FireRes"];
	skills["WaterRes"];
	skills["CloseCombat"];
	skills["fireRune"];
	skills["waterRune"];
	skills["windRune"];
	skills["iceRune"];
	skills["lightningRune"];

	skills["mining"];
	skills["fishing"];

}

//Functions
Skill& Skills::getSkill(std::string key)
{
	return skills[key];
}

const int& Skills::getSkillLvl(std::string key) const
{
	//Returns skilllevel of skill name entered
	if (skills.count(key))
		return skills.at(key).getExpNext();
	else
		throw("ERROR::Skills::Skill does not exist" + key);
}

void Skills::addExp(std::string key, const int exp)
{
	skills.at(key).addExp(exp);
}

void Skills::update(const float& dt, const sf::Vector2f mousePosView)
{
}
