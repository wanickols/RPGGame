#include "stdafx.h"
#include "Component.h"
#include "Entity.h"

Component::Component(std::string name, Entity& owner)
    : name(name), owner(owner)
{}

const std::string& Component::getName() const
{
    return name;
}

Entity& Component::getOwner() const
{
    return owner;
}
