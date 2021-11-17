#pragma once
#include "AISetting.h"

class Attribute;

class AIStun :
    public AISetting
{
public:

    AIStun(std::shared_ptr<Entity> entity, Entity& owner);
    // Inherited via AISetting
    void update(const float& dt) override;
    const bool& getStunned() const;
    void setStunned(const bool stunned);

private:
    Attribute* attributes;
    bool stunned;

};

