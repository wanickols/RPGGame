#include "stdafx.h"
#include "Lunge.h"
#include "NPC.h"
#include "Entity.h"
#include "enemyAi.h"
#include "physicsComponent.h"
#include "PhysicsDevice.h"
#include "Blackboard.h"
#include "Movement.h"

Lunge::Lunge(std::shared_ptr<BehaviorTree> tree, std::shared_ptr<Task> control)
	: LeafTask(tree, control)
{
	conditional = nullptr;
	movement = owner->getOwner().getComponent<Movement>();
	owner->keytimer.keyTimeMax = 150.f;
}

Lunge::~Lunge()
{
}

bool Lunge::initiailize(bool* conditional, std::shared_ptr<sf::Vector2f> goal)
{
	this->conditional = conditional; //pointer to bool outside of here so if something changes this can change 
	this->goal = goal;
	status = FRESH;
	return true;
}

void Lunge::run()
{
	b2Vec2 velocity = owner->getOwner().getbVectorDistance(*Task::blackboard->playerPosition);
	//Attack
	if (owner->keytimer.getKeyTime()) {
		b2Body* body = owner->getOwner().getComponent<physicsComponent>()->pDevice->findBody(owner->getOwner());
		float force = 3.f;
		body->ApplyLinearImpulseToCenter(b2Vec2({ velocity.x * force, velocity.y * force }), true);
	}
	movement->setMOVING(false);
	owner->getOwner().getComponent<enemyAi>()->setWalkSpeed(0.f);
}
