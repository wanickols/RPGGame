#include "stdafx.h"
#include "LeafTask.h"


LeafTask::LeafTask(std::shared_ptr<BehaviorTree>tree, std::shared_ptr<Task> control) : Task(tree, control)
{
}


LeafTask::~LeafTask()
{
}
