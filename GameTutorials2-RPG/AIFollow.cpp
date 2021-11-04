#include "stdafx.h"
#include "AIFollow.h"
#include "Entity.h"
#include "Movement.h"
#include "AnimationC.h"
#include "enemyAi.h"

AIFollow::AIFollow(std::shared_ptr<Entity> entity, Entity* owner)
	: AISetting("Follow", entity, owner), following(false)
{
}

void AIFollow::update(const float& dt)
{
	facing curr_direction = owner->getComponent<Movement>()->getDirection();
	if (following) {
		if(curr_direction != facing::IDLE)
		owner->getComponent<enemyAi>()->setWalkSpeed(1.f);
	}
	const float walkspeed = owner->getComponent<enemyAi>()->getWalkSpeed();

	if (curr_direction == facing::RIGHT)
	{
		owner->getComponent<AnimationC>()->play("WALKRIGHT", dt, false);
		owner->move(walkspeed, 0.f, dt);
	}
	else if (curr_direction == facing::LEFT)
	{
		owner->getComponent<AnimationC>()->play("WALKLEFT", dt, false);
		owner->move(-walkspeed, 0.f, dt);
	}
	else if (curr_direction == facing::UP)
	{
		owner->getComponent<AnimationC>()->play("WALKUP", dt, false);
		owner->move(0.f, -walkspeed, dt);
	}
	else if (curr_direction == facing::DOWN)
	{
		owner->getComponent<AnimationC>()->play("WALKDOWN", dt, false);
		owner->move(0.f, walkspeed, dt);
	}
	else
		owner->getComponent<AnimationC>()->play("DOWNIDLE", dt, false);
}

void AIFollow::reaction()
{
	const sf::Vector2f& enitityPos = entity->getCenterPosition();
	const sf::Vector2f& ownerPos = owner->getCenterPosition();

	if (owner->getDistance(enitityPos) > 25) {
		if (abs(enitityPos.x - ownerPos.x) > abs(enitityPos.y - ownerPos.y)) {
			if (enitityPos.x > ownerPos.x)
				owner->getComponent<Movement>()->setDirection(facing::RIGHT);
			else if (entity->getPosition().x < owner->getPosition().x)
				owner->getComponent<Movement>()->setDirection(facing::LEFT);
		}
		else
		{
			if (enitityPos.y > ownerPos.y)
				owner->getComponent<Movement>()->setDirection(facing::DOWN);
			else if (enitityPos.y < ownerPos.y)
				owner->getComponent<Movement>()->setDirection(facing::UP);
		}
	}else
	{
		owner->getComponent<Movement>()->halfVelocity();
		owner->getComponent<Movement>()->setDirection(facing::IDLE);
	}

}

void AIFollow::setFollowing(bool following)
{
	this->following = following;
}
