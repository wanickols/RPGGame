#include "stdafx.h"
#include "enemyAi.h"

#include "Entity.h"
#include "Movement.h"
#include "AnimationC.h"
#include "physicsComponent.h"
#include "PhysicsDevice.h"

#include "AIList.h"

enemyAi::enemyAi(std::shared_ptr<Entity> player, bool follow, bool roaming, Entity& owner)
	: Component("AI", owner), entity(player), walkSpeed(1.f), deletable(false), following(false), aggro(false), death(false)
{
	//Adding settings
		Options["Follow"] = (std::make_shared<AIFollow>(player, owner));
		OptionsList["Follow"] = true;
	
		Options["Roaming"] = (std::make_shared<AIRoaming>(player, owner));
		OptionsList["Roaming"] = true;
	
		Options["Stun"] = (std::make_shared<AIStun>(player, owner));
		OptionsList["Stun"] = true;

	movement = owner.getComponent<Movement>();
}

void enemyAi::update(const float& dt, const sf::Vector2f mousePosView)
{

	for (auto& i : Options)
	{
		i.second->update(dt);
	}

	if (!death) {
		AIStun* stun = dynamic_cast<AIStun*>(Options.at("Stun").get());
		if (!stun->getStunned()) {

			if (aggro) {
				if (OptionsList["Follow"]) {
					Options["Follow"]->setUpdateMe(true);
					following = true;
				}
				setRoaming(false);
			}

			keytimer.updateKeyTime(dt);
			facing curr_direction = movement->getDirection();
			if (following) {
				if (movement->getMOVING())
					setWalkSpeed(1.f);
				following = false;
			}
			else
			{

			}


			if (curr_direction == facing::RIGHT)
			{
				owner.getComponent<AnimationC>()->play("WALKRIGHT", dt, false);
				owner.move(walkSpeed, 0.f, dt);
			}
			else if (curr_direction == facing::LEFT)
			{
				owner.getComponent<AnimationC>()->play("WALKLEFT", dt, false);
				owner.move(-walkSpeed, 0.f, dt);
			}
			else if (curr_direction == facing::UP)
			{
				owner.getComponent<AnimationC>()->play("WALKUP", dt, false);
				owner.move(0.f, -walkSpeed, dt);
			}
			else if (curr_direction == facing::DOWN)
			{
				owner.getComponent<AnimationC>()->play("WALKDOWN", dt, false);
				owner.move(0.f, walkSpeed, dt);
			}
			else {
				owner.getComponent<AnimationC>()->play("DOWNIDLE", dt, false);
				movement->setMOVING(false);
			}
		}
	}
	else
	{

		if (owner.getComponent<AnimationC>()->play("DEATH", dt, false))
			deletable = true;

	}

	

}

void enemyAi::render(sf::RenderTarget& target, sf::Shader* shader, sf::Vector2f light_position, const bool show_hitbox)
{
	if (OptionsList["Stun"]) {
		AIStun* stun = dynamic_cast<AIStun*>(Options.at("Stun").get());
		if (stun->getStunned())
		{
			//render stun animation here
		}
	}
}

void enemyAi::reactions(const float& dt)
{
	for (auto& i : Options)
	{
		i.second->reaction(dt);
	}
}

void enemyAi::setIdle()
{
	owner.getComponent<Movement>()->setMOVING(false);
}

void enemyAi::setRoaming(bool update_roaming)
{
	if (OptionsList["Roaming"]) 
	{
		AIRoaming * roam = dynamic_cast<AIRoaming*>(Options.at("Roaming").get());
		roam->setUpdateMe(update_roaming);
	}
}

void enemyAi::setFollowing(bool update_roaming)
{
	if (OptionsList["Follow"])
	{
		AIFollow* follow = dynamic_cast<AIFollow*>(Options.at("Follow").get());
		follow->setUpdateMe(update_roaming);
	}
}

void enemyAi::setDeath(bool death)
{
	this->death = death;
	owner.getComponent<physicsComponent>()->pDevice->findBody(owner)->SetAwake(false);
}

void enemyAi::setWalkSpeed(float speed)
{
	walkSpeed = speed;
}

void enemyAi::setAggro(const bool Aggro)
{
	aggro = Aggro;
	if (!aggro)
	{
		following = false;
	}
}

void enemyAi::setStunned(const bool stunned)
{
	if (OptionsList["Stun"])
	{
		AIStun* stun = dynamic_cast<AIStun*>(Options.at("Stun").get());
		stun->setStunned(stunned);
	}
}

const float& enemyAi::getWalkSpeed()
{
	return walkSpeed;
}

const bool& enemyAi::getDeletable()
{
	return deletable;
}