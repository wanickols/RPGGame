#pragma once
#include "AISetting.h"
class AIRoaming :
    public AISetting
{
public:
    AIRoaming(std::shared_ptr<Entity> entity, Entity& owner);
    void update(const float& dt);
    void setRoaming(bool update_roaming);
private:
    bool updateRoaming;
};

