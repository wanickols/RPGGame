#pragma once
class Item;

class Inventory
{
public:

	Inventory(unsigned capacity);
	
	//Accessors
	const unsigned& size() const;
	const unsigned& maxSize() const;

	//Functions
	const bool empty() const;
	void clear();
	const bool add(Item* item);
	const bool remove(unsigned index);

	const bool saveToFile(const std::string file_name);
	const bool loadFromFile(const std::string file_name);

private:
	//Functions
	void initialize();
	void nullify(const unsigned from = 0);
	void freeMemory();
	//void expand();


	Item** itemArray;
	unsigned nrOfItems;
	unsigned capacity;

};

