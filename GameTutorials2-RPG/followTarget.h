#pragma once
#include "LeafTask.h"
class followTarget :
    public LeafTask
{
public:
    followTarget(std::shared_ptr<BehaviorTree> tree, std::shared_ptr<Task> control);
    ~followTarget();
    bool initiailize(bool* conditional, std::shared_ptr<sf::Vector2f> goal);
    // Inherited via LeafTask
    virtual void run() override;
    virtual bool addChildToTask(std::shared_ptr<Task> childTask) override;
private:
    bool* conditional;
    std::shared_ptr<sf::Vector2f> goal;
};

