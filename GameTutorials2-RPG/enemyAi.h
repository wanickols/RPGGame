#pragma once
#include "Component.h"

class AISetting;
class enemyAi :
    public Component
{
public:
    enemyAi(std::shared_ptr<Entity> player, bool follow, bool roaming, Entity& owner);
    void update(const float& dt, const sf::Vector2f mousePosView);
    void reactions();
    void setIdle();
    void setRoaming(bool update_roaming);
    void setFollowing(bool update_roaming);
    void setDeath(bool death);
    void setWalkSpeed(float speed);
    void setAggro(const bool Aggro);
    const float& getWalkSpeed();
    const bool& getDeletable();

private:
    std::map<std::string, bool> OptionsList;
    std::shared_ptr<Entity> entity;
    std::map<std::string, std::shared_ptr<AISetting>> Options;
    float walkSpeed;
};
