#pragma once
#include "LeafTask.h"
class TargetVisible :
    public LeafTask
{
public:
    TargetVisible(std::shared_ptr<BehaviorTree>tree, std::shared_ptr<Task> control);
    ~TargetVisible() {};
    // Inherited via LeafTask
    virtual void run() override;

    virtual bool addChildToTask(std::shared_ptr<Task> childTask) override { return false; };

private:

};

