#include "stdafx.h"
#include "ItemComp.h"
#include "Item.h"
#include "Entity.h"
#include "ComponentInclude.h"
#include "itemComponentInlcudes.h"
#include "Inventory.h"
#include "ItemLibrary.h"

void ItemComp::initInventory()
{
	inventory = std::make_shared<Inventory>(32);
}

ItemComp::ItemComp(Entity& owner)
	: Component("item", owner)
{
	initInventory();
}

void ItemComp::initLibrary(std::shared_ptr<ItemLibrary> item_lib)
{
	itemLib = item_lib;
}

bool ItemComp::addItem(std::string itemName, bool setActive)
{

	//MAKE LOAD FROM FILE
	std::shared_ptr<Item> item = std::make_shared<Item>();
	if (itemLib->createComponents(*item, itemName))
	{
		

		std::cout << "Inv: Before" << inventory->maxSize() << inventory->size() << std::endl;
		if (!inventory->add(item.get()))
		{
			std::cout << "inventory Full \n";
			return false;
		}
		std::cout << "Inv: After add" << inventory->maxSize() << inventory->size() << std::endl;
		
		weapons.push_back(item);//weaponComponent thing

		if (setActive) {
			activeRune = weapons.back();//sets active Rune to new rune
			owner.getComponent<Attribute>()->range = activeRune->getItemComponent<Weapon>()->getRange(); //adjust range by new range
		}
		return true;
	}
	std::cout << "ERROR::ITEMCOMP::ADDITEM : COULD NOT ADD ITEM COMPONENTS FOR " << itemName;
	return false;

}

bool ItemComp::dropItem(int index)
{
	//if(undroppable) make false

	if (!inventory->remove(index))
		return false;
	std::cout << "Inv: After remove" << inventory->maxSize() << inventory->size() << std::endl;
	return true;
}
