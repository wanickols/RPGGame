#include "stdafx.h"
#include "Weapon.h"
#include "Item.h"
#include "ItemInfo.h"

std::random_device Weapon::seed;
std::default_random_engine Weapon::engine(seed());

Weapon::Weapon(int damage, int level, int level_max, int range, int defense, Item& owner, std::string texture_file)
	: ItemComponent("weapon", owner)
{
	this->level = level;
	this->levelMax = level_max;
	this->damage = damage;
	this->range = range;
	this->defense = defense;

	if(!texture.loadFromFile(texture_file))
	{
		std::cout << "ERROR::WEAPON::COULD NOT LOAD TEXTURE \n";
	}
	sprite.setTexture(this->texture);

	this->attackTimer.restart();
	this->attackTimerMax = 500;
	std::cout << "Weapon Created\n";
}

void Weapon::update(const float& dt, const sf::Vector2f& mousePosView, const sf::Vector2f& position)
{
	sprite.setPosition(position);

	float dX = mousePosView.x - this->sprite.getPosition().x;
	float dY = mousePosView.y - this->sprite.getPosition().y;

	const float PI = 3.14159265f;
	float deg = atan2(dY, dX) * 360 / PI;

	if (this->attackTimer.getElapsedTime().asMilliseconds() < this->attackTimerMax / 4)
	{
	   float len = std::sqrt((float)pow(dX, 2) + (float)pow(dY, 2));
		sf::Vector2f normVec(dX / len, dY / len);
		this->sprite.setPosition(position.x + normVec.x * 10.f, position.y + normVec.y * 10.f);
	}
	else
		this->sprite.setRotation(deg);
}

void Weapon::render(sf::RenderTarget& target, sf::Shader* shader, sf::Vector2f light_position, const bool show_hitbox)
{
	if (shader)
		target.draw(this->sprite, shader);
	else
		target.draw(this->sprite);
}

void Weapon::generateLevel(ItemRarity rarity)
{
	if(rarity == ItemRarity::Unique) //unique
		return;


	std::bernoulli_distribution rareUp(.1);
	int mean = rarity * 3;

	if (rareUp(engine))
		++mean;
	
	std::normal_distribution<float> levelRange(mean, 1.f);
	level = levelRange(engine);

	if (level > levelMax)
		level = levelMax;
	if (level < 1)
		level = 1;
	owner->getItemComponent<ItemInfo>()->setLevel(level);
	owner->getItemComponent<ItemInfo>()->calculateValue();
}

const int Weapon::getRange() const
{
	return range;
}

const bool Weapon::getAttackTimer()
{
	if(attackTimer.getElapsedTime().asMilliseconds() >= attackTimerMax)
	{
		attackTimer.restart();
		return true;
	}

	return false;
}
