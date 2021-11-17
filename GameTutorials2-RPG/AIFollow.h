#pragma once
#include "AISetting.h"

class AIFollow :
    public AISetting
{
public:
    AIFollow(std::shared_ptr<Entity> entity, Entity& owner);
    void update(const float& dt);
    void reaction(const float& dt) override;

private:
   
    sf::Vector2f lastTarget;
    sf::Vector2f speed;
    //std::shared_ptr<std::list<graphNode*>> path;
  
};

