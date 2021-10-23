#include "stdafx.h"
#include "ItemComp.h"
#include "Item.h"
#include "Entity.h"
#include "ComponentInclude.h"
#include "itemComponentInlcudes.h"
#include "Inventory.h"

void ItemComp::initInventory()
{
	inventory = std::make_shared<Inventory>(32);
}

ItemComp::ItemComp(Entity* owner)
	: Component("item", owner)
{
	initInventory();
}

bool ItemComp::addItem()
{

	//MAKE LOAD FROM FILE
	std::shared_ptr<Item> fr = std::make_shared<Item>();
	std::shared_ptr<ItemInfo> info = std::make_shared<ItemInfo>(0, "Fire Rune",
		"A fiery red stone hot to the touch and incredibely dense. \n Its origin is unknown, but it enables the user to shoot fire when placed in his hand.",//description
		ItemRarity::Unique, ItemClasses::RUNE, *fr); //Info
	fr->addItemComponent(info);

	std::shared_ptr<Weapon> weapon = std::make_shared<Weapon>(25, 25, 2, *fr, "Resources/Images/Sprites/Items/Firerune.png");
	fr->addItemComponent(weapon);

	weapons.push_back(fr);//itemComponent addComponent
	activeRune = weapons.back();

	std::shared_ptr<RuneComponent> runeComp = std::make_shared<RuneComponent>("Resources/Images/Sprites/Bullets/FIRE_BULLET.png", *fr);
	fr->addItemComponent(runeComp);
	
	

	owner->getComponent<Attribute>()->range = activeRune->getItemComponent<Weapon>()->getRange();

	std::cout << "Inv: Before" << inventory->maxSize() << inventory->size() << std::endl;
	inventory->add(weapons.back().get());
	std::cout << "Inv: After add" << inventory->maxSize() << inventory->size() << std::endl;
	inventory->remove(0);
	std::cout << "Inv: After remove" << inventory->maxSize() << inventory->size() << std::endl;

	return true;
}
