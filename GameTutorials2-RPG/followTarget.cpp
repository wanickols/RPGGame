#include "stdafx.h"
#include "followTarget.h"
#include "NPC.h"
#include "Entity.h"
#include "physicsComponent.h"
#include "Movement.h"
#include "PhysicsDevice.h"
#include "Blackboard.h"

followTarget::followTarget(std::shared_ptr<BehaviorTree> tree, std::shared_ptr<Task> control)
	: LeafTask(tree, control)
{
	conditional = nullptr;
}

followTarget::~followTarget()
{
}

bool followTarget::initiailize(bool* conditional, std::shared_ptr<sf::Vector2f> goal)
{
	this->conditional = conditional; //pointer to bool outside of here so if something changes this can change 
	this->goal = goal;
	status = FRESH;
	return false;
}

void followTarget::run()
{

	if (conditional) //attacking or something else where we want to skip this task
	{
		sf::Vector2f enemyPos = owner->getOwner().getComponent<physicsComponent>()->pDevice->getPosition(owner->getOwner());
		
		if(owner->getOwner().getDistance(*Task::blackboard->playerPosition) < 50)
		{
			success(); // go onto lunge
		}
		else {

			if (abs(enemyPos.x - goal->x) > abs(enemyPos.y - goal->y))
			{
				if (enemyPos.x - goal->x > 0) // enemy to the right of the player
				{
					owner->getOwner().getComponent<Movement>()->setDirection(facing::LEFT);
				}
				else
				{
					owner->getOwner().getComponent<Movement>()->setDirection(facing::RIGHT);
				}
			}
			else if (enemyPos.y - goal->y > 0) //Enemy Is below player
			{
				owner->getOwner().getComponent<Movement>()->setDirection(facing::UP);
			}
			else
			{
				owner->getOwner().getComponent<Movement>()->setDirection(facing::DOWN);
			}
			running();
		}
	}
	
		

}

bool followTarget::addChildToTask(std::shared_ptr<Task> childTask)
{
	return false;
}

