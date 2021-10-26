#pragma once
#include "ItemPresets.h"
class Item;

struct ItemComponentLibrary
{
	ItemComponentLibrary();
	std::shared_ptr<allItemPresets> add(tinyxml2::XMLElement*);
	std::map<std::string, int> componentTypes;

	void addInfo(tinyxml2::XMLElement*, std::shared_ptr<allItemPresets> presets);
	void addSprite(tinyxml2::XMLElement*, std::shared_ptr<allItemPresets> presets);
	void addWeapon(tinyxml2::XMLElement*, std::shared_ptr<allItemPresets> presets);
	void addRune(tinyxml2::XMLElement*, std::shared_ptr<allItemPresets> presets);
};


class ItemLibrary
{
public:
	ItemLibrary();
	void initComponents();
	bool createComponents(Item& owner, std::string name);
private:
	tinyxml2::XMLDocument componentDoc;
	ItemComponentLibrary itemComponentlib;
	std::map<int, std::string> types; //assigning names to numbers
	std::map<std::string, std::shared_ptr<allItemPresets>> itemPresets;
};

