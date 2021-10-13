#include "stdafx.h"
#include "Component.h"
#include "Entity.h"

Component::Component(std::string name, Entity* owner)
{
    this->name = name;
    this->owner = std::make_shared<Entity>(*owner);
}

const std::string& Component::getName() const
{
    return name;
}
