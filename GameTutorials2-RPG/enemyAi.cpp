#include "stdafx.h"
#include "enemyAi.h"
#include "Movement.h"
#include "AnimationC.h"
#include "Entity.h"
#include "AIFollow.h"
#include "AIRoaming.h"

enemyAi::enemyAi(std::shared_ptr<Entity> player, bool follow, bool roaming, Entity* owner)
	: Component("AI", owner), entity(player), walkSpeed(1.f)
{
	//Adding settings
	if (follow) {
		Options["Follow"] = (std::make_shared<AIFollow>(player, owner));
		OptionsList["Follow"] = true;
	}
	if (roaming) {
		Options["Roaming"] = (std::make_shared<AIRoaming>(player, owner));
		OptionsList["Roaming"] = true;
	}

}

void enemyAi::update(const float& dt, const sf::Vector2f mousePosView)
{
	walkSpeed /= 2;
	for (auto& i : Options)
	{
		i.second->update(dt);
	}
	
}

void enemyAi::reactions()
{
	for (auto& i : Options)
	{
		i.second->reaction();
	}
}

void enemyAi::setIdle()
{
	owner->getComponent<Movement>()->setDirection(facing::IDLE);
}

void enemyAi::setRoaming(bool update_roaming)
{
	if (OptionsList["Roaming"]) 
	{
		AIRoaming * roam = dynamic_cast<AIRoaming*>(Options.at("Roaming").get());
		roam->setRoaming(update_roaming);
	}
}

void enemyAi::setFollowing(bool update_roaming)
{
	if (OptionsList["Follow"])
	{
		AIFollow* follow = dynamic_cast<AIFollow*>(Options.at("Follow").get());
		follow->setFollowing(update_roaming);
	}
}

void enemyAi::setWalkSpeed(float speed)
{
	walkSpeed = speed;
}

const float& enemyAi::getWalkSpeed()
{
	return walkSpeed;
}
