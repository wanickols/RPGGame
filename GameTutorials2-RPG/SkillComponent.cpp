#include "stdafx.h"
#include "SkillComponent.h"

SkillComponent::SkillComponent()
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
Skill& SkillComponent::getSkill(std::string key)
{
	return skills[key];
}

const int& SkillComponent::getSkillLvl(std::string key) const
{
	//Returns skilllevel of skill name entered
	if (skills.count(key))
		return skills.at(key).getExpNext();
	else
		throw("ERROR::SKILLCOMPONENT::Skill does not exist" + key);
}

void SkillComponent::addExp(std::string key, const int exp)
{
	skills.at(key).addExp(exp);
}
