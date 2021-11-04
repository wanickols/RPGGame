#pragma once
#include "AISetting.h"
class AIFollow :
    public AISetting
{
public:
    AIFollow(std::shared_ptr<Entity> entity, Entity* owner);
    void update(const float& dt);
    void reaction() override;
    void setFollowing(bool following);
private:
    bool following;
};

