#include "stdafx.h"
#include "Constants.h"
#include "NPC.h"
#include "Blackboard.h"
#include "physicsComponent.h"
#include "Entity.h"
#include "Selector.h"
#include "Sequence.h"
#include "Task.h"
#include "BehaviorTree.h"
#include "BranchTask.h"
#include "PhysicsDevice.h"
#include "LeafList.h"



NPC::NPC(std::shared_ptr<Entity> owner)
	: Component("NPC", *owner)
{
	npcOwner = owner;
	*follow = true;
}


NPC::~NPC()
{
}

void NPC::Initialize()
{
	//set the initial position for this object.
	//Task::blackboard->enemyOrigins[owner] = owner->GetComponent<Sprite>()->position;
	
	//create behavior tree
	Task::blackboard->enemyOrigins[npcOwner] = npcOwner->getComponent<physicsComponent>()->pDevice->getPosition(*npcOwner);

	////create behavior tree
	behaviorTree = std::make_shared<BehaviorTree>(*this);

	//root of tree is a selector
	std::shared_ptr<Selector> decideBehavior = std::make_shared<Selector>(behaviorTree, nullptr);
	behaviorTree->addChild(decideBehavior);

	//add sequences (in order) to selector
	std::shared_ptr<Sequence> chaseEnemy = std::make_shared<Sequence>(behaviorTree, decideBehavior);
	decideBehavior->addChild(chaseEnemy);

	//add leaf tasks to sequence
	std::shared_ptr<TargetVisible> enemyVis = std::make_shared<TargetVisible>(behaviorTree, chaseEnemy); //condition
	chaseEnemy->addChild(enemyVis);

	std::shared_ptr<followTarget> turnTowardEnemy = std::make_shared<followTarget>(behaviorTree, chaseEnemy); //action
	turnTowardEnemy->initiailize(follow, Task::blackboard->playerPosition);
	chaseEnemy->addChild(turnTowardEnemy);

		//	//add leaf tasks to sequence
		//	TurnToward* turnTowardEnemy = new TurnToward(behaviorTree, chaseEnemy);
		//	chaseEnemy->addChild(turnTowardEnemy);

		//	MoveToward* moveTowardEnemy = new MoveToward(behaviorTree, chaseEnemy);
		//	chaseEnemy->addChild(moveTowardEnemy);
		//
		//Sequence* returnToOrigin = new Sequence(behaviorTree, decideBehavior);
		//decideBehavior->addChild(returnToOrigin);
		//	//add leaf tasks to sequence
		//	TurnToward* turnTowardEnemy = new TurnToward(behaviorTree, returnToOrigin);
		//	returnToOrigin->addChild(turnTowardEnemy);

		//	MoveToward* moveTowardEnemy = new MoveToward();
		//	returnToOrigin->addChild(moveTowardEnemy);
		//	
		//Spin* patrol = new Spin(behaviorTree, decideBehavior);
		//patrol->initiailize();
		//decideBehavior->addChild(patrol);
		//

	


}

void NPC::update(const float& dt, const sf::Vector2f mousePosView)
{
	keytimer.updateKeyTime(dt);
}

void NPC::Finish()
{

}
