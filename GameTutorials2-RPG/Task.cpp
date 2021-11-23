#include "stdafx.h"
#include "Task.h"
#include "Blackboard.h"
#include "NPC.h"
#include "BehaviorTree.h"

std::shared_ptr<Blackboard> Task::blackboard = nullptr;

Task::Task(NPC& owner)
{
	control = nullptr;
	this->owner = std::make_shared<NPC>(*tree->owner);
	tree = nullptr;
}

Task::Task(std::shared_ptr<BehaviorTree> tree, std::shared_ptr<Task> control)
{
	this->owner = std::make_shared<NPC>(*tree->owner);
	this->tree = tree;
	this->control = control;
}


Task::~Task()
{
}

void Task::start()
{
	
}

void Task::end()
{
}

void Task::resetTask()
{
	status = FRESH;

}

void Task::running()
{
	control->childRunning();
	status = RUNNING;	
}

void Task::success()
{
	control->childSuccess();
	status = SUCEEDED;
	end();
}

void Task::fail()
{
	control->childFail();
	status = FAILED;
	end();
}

void Task::cancel()
{
	if(status == RUNNING)
		status = CANCELLED;
}

bool Task::addChild(std::shared_ptr<Task> childTask)
{
	return (addChildToTask(childTask));
}
