#pragma once
#include "AISetting.h"

#include "Movement.h"

class AIRoaming :
    public AISetting
{
public:
    AIRoaming(std::shared_ptr<Entity> entity, Entity& owner);
    void update(const float& dt);
    void setRoaming(bool update_roaming);
private:

    bool repeatRoam;
    int repeatCounter;
    facing lastDirection;
};

