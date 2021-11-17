#include "stdafx.h"
#include "AISetting.h"
#include "Entity.h"
#include "Movement.h"
#include "AnimationC.h"
#include "enemyAi.h"

AISetting::AISetting(std::string name, std::shared_ptr<Entity> entity, Entity& owner)
	: owner(owner), name(name), entity(entity), spawner(nullptr)
{
	movement = owner.getComponent<Movement>();
}


const std::string& AISetting::getName() const
{
	return name;
}



void AISetting::setUpdateMe(bool update)
{
	updateMe = update;
}
