#include "stdafx.h"
#include "ItemInfo.h"

ItemInfo::ItemInfo(int value, std::string name, std::string desc, short rarity, short item_class, Item& owner)
	: ItemComponent("info", owner)
{
	this->value = value;
	this->name = name;
	description = desc;
	itemClass = item_class;
}

const int ItemInfo::getValue() const
{
	return value;
}

const std::string ItemInfo::getName() const
{
	return name;
}

const std::string ItemInfo::getDescription() const
{
	return description;
}

const short ItemInfo::getClass() const
{
	return itemClass;
}

void ItemInfo::setValue(int value)
{
	this->value = value;
}

void ItemInfo::setName(std::string& name)
{
	this->name = name;
}

void ItemInfo::setDescription(std::string& desc)
{
	description = desc;
}

void ItemInfo::setClass(short item_class)
{
	itemClass = item_class;
}
