#pragma once
#include "LeafTask.h"

class Movement;

class Lunge :
    public LeafTask
{
public:
    Lunge(std::shared_ptr<BehaviorTree> tree, std::shared_ptr<Task> control);
    ~Lunge();
    bool initiailize(bool* conditional, std::shared_ptr<sf::Vector2f> goal);
    // Inherited via LeafTask
    virtual void run() override;
    virtual bool addChildToTask(std::shared_ptr<Task> childTask) override { return false;  };
private:

    bool* conditional;
    std::shared_ptr<sf::Vector2f> goal;
    Movement* movement;
};

