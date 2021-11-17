#include "stdafx.h"
#include "AIRoaming.h"
#include "Entity.h"
#include "EnemyData.h"
#include "enemyAi.h"
#include "Movement.h"

std::random_device AISetting::seed;
std::default_random_engine AISetting::engine(seed());

AIRoaming::AIRoaming(std::shared_ptr<Entity> entity, Entity& owner)
	: AISetting("Roaming", entity, owner), repeatRoam(false), repeatCounter(0)
{
	spawner = owner.getComponent<EnemyData>()->getOrigin();
}

void AIRoaming::update(const float& dt)
{

	//if enemy is not following player
	if(updateMe)
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
				movement->move(moveVec.x, moveVec.y, dt);
				//owner.getComponent<Movement>()->setDirection(facing::IDLE);
		}
		//if enemy is in range of spawner
		else
		{
			if (repeatRoam) {
				
				movement->setDirection(lastDirection);

				if(--repeatCounter == 0)
				{
					repeatRoam = false;
				}


			}
			else {
				
				std::bernoulli_distribution changeMoveChance(.01f);
				if (changeMoveChance(engine)) {


					repeatRoam = true;
					repeatCounter = 3;
					std::uniform_int_distribution<int> movementChance(0, 2);
					owner.getComponent<enemyAi>()->setWalkSpeed(1.f);
					switch (movementChance(engine))
					{
					case(0):
						lastDirection = facing::LEFT;
						break;
					case(1):
						lastDirection = facing::RIGHT;
						break;
					case(2):
						lastDirection = facing::UP;
						break;
					case(3):
						lastDirection = facing::DOWN;
						break;
					default:
						lastDirection = facing::DOWN;
						owner.getComponent<enemyAi>()->setWalkSpeed(0.f);
						break;
					}
					movement->setDirection(lastDirection);
				}
				else
				{
					owner.getComponent<enemyAi>()->setWalkSpeed(0.f);
				}

			}
		}
	}
}
