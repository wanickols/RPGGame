#include "stdafx.h"
#include "ItemLibrary.h"
#include "itemComponentInlcudes.h"
#include "Item.h"

void ItemLibrary::initComponents()
{
	//Components
	if (componentDoc.LoadFile("itemGeneration.xml") != tinyxml2::XML_SUCCESS)
	{
		std::cout << "ERROR::ITEMLIBRARY::COMPONENT XML FILE COULD NOT LOAD \n" << "itemGeneration.xml";
		exit(1);
	}

	tinyxml2::XMLElement* compRoot = componentDoc.FirstChildElement("Map"); //root of xml
	tinyxml2::XMLElement* item_1 = compRoot->FirstChildElement("Item");
	tinyxml2::XMLElement* component;

	while (item_1) { //loops until no more enemies exist
		component = item_1->FirstChildElement("Component");
		itemPresets[item_1->Attribute("name")] = (itemComponentlib.add(component));//adds presets to names of enemies listed in file

		item_1 = item_1->NextSiblingElement();
	}
}

bool ItemLibrary::createComponents(Item& owner, std::string name)
{
	bool anyCreated = false; //keeps from adding empty items
	//0
	if (itemPresets.find(name)->second->info.created)
	{
		std::shared_ptr<ItemInfoPreset> iP = std::make_shared<ItemInfoPreset>(itemPresets.find(name)->second->info);
		std::shared_ptr<ItemInfo> info = std::make_shared<ItemInfo>(iP->value, iP->level, iP->name, iP->description, (ItemRarity)iP->rarity, (ItemClasses)iP->item_class, owner);
		owner.addItemComponent(info);
		anyCreated = true;
	}
	//1
	if (itemPresets.find(name)->second->spriteP.created)
	{
		std::shared_ptr<ItemSpritePreset> sP = std::make_shared<ItemSpritePreset>(itemPresets.find(name)->second->spriteP);

		std::shared_ptr<itemSprite> sprite = std::make_shared<itemSprite>(sP->sprite, sP->texture,sP->width, sP->height, owner);
		owner.addItemComponent(sprite);
		anyCreated = true;
	}
	//2
	if (itemPresets.find(name)->second->weapon.created)
	{
		std::shared_ptr<ItemWeaponPreset> wP = std::make_shared<ItemWeaponPreset>(itemPresets.find(name)->second->weapon);
		std::shared_ptr<Weapon> weapon = std::make_shared<Weapon>(wP->damage, wP->level,wP->levelMax, wP->range, wP->defense, owner, wP->textureFile);
		weapon->generateLevel(owner.getItemComponent<ItemInfo>()->getRarity());
		owner.addItemComponent(weapon);
		anyCreated = true;
	}
	//3
	if (itemPresets.find(name)->second->rune.created)
	{
		std::shared_ptr<ItemRunePreset> rP = std::make_shared<ItemRunePreset>(itemPresets.find(name)->second->rune);
		std::shared_ptr<RuneComponent> rune = std::make_shared<RuneComponent>(rP->bulletTexture, owner);
		owner.addItemComponent(rune);
		anyCreated = true;
	}

	return anyCreated;
}

ItemLibrary::ItemLibrary()
{
	initComponents();
}

ItemComponentLibrary::ItemComponentLibrary()
{
	componentTypes["info"] = 0;
	componentTypes["sprite"] = 1;
	componentTypes["weapon"] = 2;
	componentTypes["rune"] = 3;
	//future
	componentTypes["animation"] = 4;
	componentTypes["hitbox"] = 5;
}

std::shared_ptr<allItemPresets> ItemComponentLibrary::add(tinyxml2::XMLElement* component)
{
	std::shared_ptr<allItemPresets> presets = std::make_shared<allItemPresets>();
	while (component) {
		if (component->IntAttribute("type") == componentTypes.find("info")->second)//0
			addInfo(component, presets);
		else if (component->IntAttribute("type") == componentTypes.find("sprite")->second)//1
			addSprite(component, presets);
		else if (component->IntAttribute("type") == componentTypes.find("weapon")->second)//2
			addWeapon(component, presets);
		else if (component->IntAttribute("type") == componentTypes.find("rune")->second)//3
			addRune(component, presets);
		else if (component->IntAttribute("type") == componentTypes.find("animation")->second) //5
			std::cout << "make me \n";
		else if (component->IntAttribute("type") == componentTypes.find("hitbox")->second) //7
			std::cout << "make me \n";
		component = component->NextSiblingElement();
	}
	return presets;
}

void ItemComponentLibrary::addInfo(tinyxml2::XMLElement* component, std::shared_ptr<allItemPresets> presets)
{
	presets->info.created = true;
	presets->info.name = component->Attribute("name");
	presets->info.description = component->Attribute("description");
	component->QueryIntAttribute("value", &presets->info.value);
	component->QueryIntAttribute("level", &presets->info.level);
	component->QueryIntAttribute("rarity", &presets->info.rarity);
	component->QueryIntAttribute("item_class", &presets->info.item_class);


}

void ItemComponentLibrary::addSprite(tinyxml2::XMLElement* component, std::shared_ptr<allItemPresets> presets)
{
	presets->spriteP.created = true;
	presets->spriteP.textureFile = component->Attribute("textureFile");
	//Sprite
	if(!presets->spriteP.texture.loadFromFile(presets->spriteP.textureFile))
	{
		std::cout << "ERROR::ITEMCOMPONENTLIBRARY::COULD NOT LOAD SPRITE: " << presets->spriteP.textureFile << "\n";
	}
	presets->spriteP.sprite.setTexture(presets->spriteP.texture);
	component->QueryIntAttribute("width", &presets->spriteP.width);
	component->QueryIntAttribute("height", &presets->spriteP.height);
}

void ItemComponentLibrary::addWeapon(tinyxml2::XMLElement* component, std::shared_ptr<allItemPresets> presets)
{
	presets->weapon.created = true;
	presets->weapon.textureFile = component->Attribute("textureFile");
	component->QueryIntAttribute("damage", &presets->weapon.damage);
	component->QueryIntAttribute("range", &presets->weapon.range);
	component->QueryIntAttribute("level", &presets->weapon.level);
	component->QueryIntAttribute("levelMax", &presets->weapon.levelMax);
	component->QueryIntAttribute("defense", &presets->weapon.defense);
}

void ItemComponentLibrary::addRune(tinyxml2::XMLElement* component, std::shared_ptr<allItemPresets> presets)
{
	presets->rune.created = true;
	presets->rune.bulletTexture = component->Attribute("bulletTexture");

}
