#pragma once
#include "stdafx.h"

struct ItemInfoPreset 
{
	bool created = false;
	int value;
	int level;
	std::string name; 
	std::string description;
	int rarity;
	int item_class;
};
struct ItemSpritePreset 
{
	bool created = false;
	std::string textureFile;
	sf::Texture texture;
	sf::Sprite sprite;
	int width;
	int height;
};
struct ItemWeaponPreset 
{
	bool created = false;
	int damage;  
	int level; 
	int levelMax; 
	int range; 
	int defense; 
	std::string textureFile;
};
struct ItemRunePreset 
{
	bool created = false;
	std::string bulletTexture;
};


struct allItemPresets 
{
	ItemInfoPreset info;
	ItemSpritePreset spriteP;
	ItemWeaponPreset weapon;
	ItemRunePreset rune;
};