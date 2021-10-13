#include "stdafx.h"
#include "Component.h"

Component::Component()
{
    name = "DEFUALT COMPONENT";
}

const std::string& Component::getName() const
{
    return name;
}
