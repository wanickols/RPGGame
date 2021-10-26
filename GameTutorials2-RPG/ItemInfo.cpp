#include "stdafx.h"
#include "ItemInfo.h"
#include "Item.h"
#include "Weapon.h"

ItemInfo::ItemInfo(int value, int level, std::string name, std::string desc, short rarity, short item_class, Item& owner)
	: ItemComponent("info", owner)
{
	this->value = value;
	this->name = name;
	this->rarity = rarity;
	this->level = level;
	description = desc;
	itemClass = item_class;
}

int ItemInfo::getValue() const
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

const int ItemInfo::getLevel() const
{
	return level;
}

const short ItemInfo::getRarityS() const
{
	return rarity;
}

const ItemRarity ItemInfo::getRarity() const
{
	return (ItemRarity)rarity;
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

void ItemInfo::calculateValue()
{
	float increase = rarity * rarity * 50.f;
	increase *= level / 5.f;
	//quality
	//damage
	if (owner->getItemComponent<Weapon>() != nullptr)
	{
		increase = increase * 1.4f;
	}
	value += (int)increase;

}

void ItemInfo::setLevel(const int level)
{
	this->level = level;
}
