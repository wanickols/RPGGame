#include "stdafx.h"
#include "Item.h"
#include "Inventory.h"
void Inventory::initialize()
{
	
	nrOfItems = 0;
	//couldn't figure out with smart pointer :D
	itemArray = new Item * [capacity];

	nullify();
}

Inventory::Inventory(unsigned capacity)
{
	this->capacity = capacity;
	initialize();
}

const unsigned& Inventory::size() const
{
	return nrOfItems;
}

const unsigned& Inventory::maxSize() const
{
	return capacity;
}

const bool Inventory::empty() const
{
	return nrOfItems == 0;
}

void Inventory::clear()
{
	for (int i = 0; i < capacity; i++)
	{
		delete itemArray[i];
	}
	
	this->nrOfItems = 0;

	this->nullify();
}

const bool Inventory::add(Item* item)
{
	if (nrOfItems < capacity)
	{
		itemArray[nrOfItems++] = item->clone();
		return true;
	}
	std::cout << "INVENTORY:: FAILED TO ADD ITEM: INVENTORY FULL ";
		return false;
}

const bool Inventory::remove(unsigned index)
{
	if (nrOfItems > 0) {
		if (index < 0 || index >= capacity) {
			std::cout << "INVENTORY:: FAILED TO REMOVE ITEM: INDEX INVALID";
			return false;
		}
		
		delete itemArray[index];
		itemArray[index] = nullptr;
		return true;   
	}
	return false;
}

const bool Inventory::saveToFile(const std::string file_name)
{
	return false;
}

const bool Inventory::loadFromFile(const std::string file_name)
{
	return false;
}

void Inventory::nullify(const unsigned from)
{
	for (int i = from; i < nrOfItems; i++)
	{
		itemArray[i] = nullptr;
	}
}

void Inventory::freeMemory()
{
	//Nullifies everything from parameter to capactiy;
	for (int i = 0; i < capacity; i++)
	{
		delete itemArray[i];
	}
	delete[] itemArray;
	
}
