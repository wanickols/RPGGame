#include "stdafx.h"
#include "ItemComponent.h"
#include "Item.h"

ItemComponent::ItemComponent(std::string componentName, Item& owner)
{
	this->componentName = componentName;
	this->owner = std::make_shared<Item>(owner);
}

const std::string ItemComponent::getComponentName() const
{
	return componentName;
}
