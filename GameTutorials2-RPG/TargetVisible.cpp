#include "stdafx.h"
#include "TargetVisible.h"
#include "AnimationC.h"
#include "NPC.h"
#include "Entity.h"
#include "Blackboard.h"
#include "b2_shape.h"

TargetVisible::TargetVisible(std::shared_ptr<BehaviorTree> tree, std::shared_ptr<Task> control)
	: LeafTask(tree, control)
{}

void TargetVisible::run()
{

	if(owner->getOwner().getDistance(*Task::blackboard->playerPosition) > 200)
	{
		success(); // will move onto next item;
	}
	else
	{
		fail(); //will repeat this until it works
	}
}
