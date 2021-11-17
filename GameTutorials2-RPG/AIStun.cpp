#include "stdafx.h"
#include "AIStun.h"
#include "Entity.h"
#include "Attribute.h"

AIStun::AIStun(std::shared_ptr<Entity> entity, Entity& owner)
	: AISetting("Stun", entity, owner), stunned(false)
{

	attributes = owner.getComponent<Attribute>();
	keytimer.keyTimeMax = attributes->stunTime; //stun duration
}

void AIStun::update(const float& dt)
{
	if(updateMe)
	{
		if (stunned) {
			keytimer.updateKeyTime(dt);
			if (keytimer.getKeyTime()) //checking if stun is over
			{
				attributes->stunResistance *= 2.5;
				stunned = false;
			}
		}
		
	}
}

const bool& AIStun::getStunned() const
{
	return stunned;
}

void AIStun::setStunned(const bool stunned)
{
	this->stunned = stunned;
}
