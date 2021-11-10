#include "stdafx.h"
#include "AIRoaming.h"
#include "Entity.h"
#include "EnemyData.h"
#include "enemyAi.h"
#include "Movement.h"

std::random_device AISetting::seed;
std::default_random_engine AISetting::engine(seed());

AIRoaming::AIRoaming(std::shared_ptr<Entity> entity, Entity& owner)
	: AISetting("Roaming", entity, owner), updateRoaming(true)
{
	spawner = owner.getComponent<EnemyData>()->getOrigin();
}

void AIRoaming::update(const float& dt)
{
	//if enemy is not following player
	if(updateRoaming)
	{
		//If enemy goes out too far away from spawner
		if (owner.getDistance(spawner->getPosition()) > spawner->maxDistance)
		{
			owner.getComponent<enemyAi>()->setWalkSpeed(0.f);
				sf::Vector2f moveVec;
				moveVec.x = spawner->getPosition().x - owner.getPosition().x;
				moveVec.y = spawner->getPosition().y - owner.getPosition().y;
				float vecLength = sqrt(pow(moveVec.x, 2) + pow(moveVec.x, 2));
				moveVec /= vecLength;
				owner.getComponent<Movement>()->move(moveVec.x, moveVec.y, dt);
				//owner.getComponent<Movement>()->setDirection(facing::IDLE);
		}
		//if enemy is in range of spawner
		else
		{
			std::bernoulli_distribution changeMoveChance(.01f);
			if (changeMoveChance(engine)) {
				std::uniform_int_distribution<int> movementChance(0, 5);
				owner.getComponent<enemyAi>()->setWalkSpeed(10.f);
				switch (movementChance(engine))
				{
				case(0):
					owner.getComponent<Movement>()->setDirection(facing::LEFT);
					break;
				case(1):
					owner.getComponent<Movement>()->setDirection(facing::RIGHT);
					break;
				case(2):
					owner.getComponent<Movement>()->setDirection(facing::UP);
					break;
				case(3):
					owner.getComponent<Movement>()->setDirection(facing::DOWN);
					break;
				default:
					owner.getComponent<Movement>()->setDirection(facing::DOWN);
					break;
				}
			}
		}
		
	}
}

void AIRoaming::setRoaming(bool update_roaming)
{
	updateRoaming = update_roaming;
}
