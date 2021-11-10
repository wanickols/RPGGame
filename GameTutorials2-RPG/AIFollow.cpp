#include "stdafx.h"
#include "AIFollow.h"
#include "Entity.h"
#include "Movement.h"
#include "AnimationC.h"
#include "enemyAi.h"
#include "Combat.h"
#include "PhysicsDevice.h"
#include "physicsComponent.h"

AIFollow::AIFollow(std::shared_ptr<Entity> entity, Entity& owner)
	: AISetting("Follow", entity, owner), following(false), death(false)
{
	keytimer.keyTimeMax = 150.f;
	aggro = false;
}

void AIFollow::update(const float& dt)
{
	if (!death) {
		if (aggro) {
			reaction();
			following = true;
			owner.getComponent<enemyAi>()->setRoaming(false);
		}

		keytimer.updateKeyTime(dt);
		facing curr_direction = owner.getComponent<Movement>()->getDirection();
		if (following) {
			if (owner.getComponent<Movement>()->getMOVING())
				owner.getComponent<enemyAi>()->setWalkSpeed(1.f);
			following = false;
		}


		const float walkspeed = owner.getComponent<enemyAi>()->getWalkSpeed();

		if (walkspeed < 1.f / 32.f)
		{
			owner.getComponent<enemyAi>()->setWalkSpeed(1.f / 4.f);
		}

		if (curr_direction == facing::RIGHT)
		{
			owner.getComponent<AnimationC>()->play("WALKRIGHT", dt, false);
			owner.move(walkspeed, 0.f, dt);
		}
		else if (curr_direction == facing::LEFT)
		{
			owner.getComponent<AnimationC>()->play("WALKLEFT", dt, false);
			owner.move(-walkspeed, 0.f, dt);
		}
		else if (curr_direction == facing::UP)
		{
			owner.getComponent<AnimationC>()->play("WALKUP", dt, false);
			owner.move(0.f, -walkspeed, dt);
		}
		else if (curr_direction == facing::DOWN)
		{
			owner.getComponent<AnimationC>()->play("WALKDOWN", dt, false);
			owner.move(0.f, walkspeed, dt);
		}
		else
			owner.getComponent<AnimationC>()->play("DOWNIDLE", dt, false);
	}
	else
	{

		if(owner.getComponent<AnimationC>()->play("DEATH", dt, false))
			deletable = true;
		
	}
}

void AIFollow::reaction()
{
	const sf::Vector2f& enitityPos = entity->getCenterPosition();
	const sf::Vector2f& ownerPos = owner.getCenterPosition();

	b2Vec2 velocity = owner.getbVectorDistance(enitityPos);
		if (owner.getDistance(enitityPos) > 100) {
			if (abs(enitityPos.x - ownerPos.x) > abs(enitityPos.y - ownerPos.y)) {
				if (enitityPos.x > ownerPos.x)
					owner.getComponent<Movement>()->setDirection(facing::RIGHT);
				else if (entity->getPosition().x < owner.getPosition().x)
					owner.getComponent<Movement>()->setDirection(facing::LEFT);
			}
			else
			{
				if (enitityPos.y > ownerPos.y)
					owner.getComponent<Movement>()->setDirection(facing::DOWN);
				else if (enitityPos.y < ownerPos.y)
					owner.getComponent<Movement>()->setDirection(facing::UP);
			}
		}
		else
		{
			if (keytimer.getKeyTime()) {
				b2Body* body = owner.getComponent<physicsComponent>()->pDevice->findBody(owner);
				float force = 4.f;
				body->ApplyLinearImpulseToCenter(b2Vec2({ velocity.x * force, velocity.y * force }), true);
			}
			owner.getComponent<Movement>()->setMOVING(false);
		}
}

void AIFollow::setFollowing(bool following)
{
	this->following = following;
}

void AIFollow::setDeath(bool death)
{
	this->death = death;
	owner.getComponent<physicsComponent>()->pDevice->findBody(owner)->SetAwake(false);
}

void AIFollow::setAggro(const bool aggro)
{
	this->aggro = aggro;
}
