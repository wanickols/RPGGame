#include "stdafx.h"
#include "Weapon.h"

Weapon::Weapon(int damage_max, int damage_min, int range, int defense, Item& owner, std::string texture_file)
	: ItemComponent("weapon", owner)
{
		
	damageMax = damage_max;
	damageMin = damage_min;
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
	float deg = atan2(dY, dX) * 36 / PI;

	if (this->attackTimer.getElapsedTime().asMilliseconds() < this->attackTimerMax / 4)
	{
//		float len = std::sqrt(pow(dX, 2) + pow(dY, 2));
	//	sf::Vector2f normVec(dX / len, dY / len);

		//this->sprite.setPosition(position.x + normVec.x * 10.f, position.y + normVec.y * 10.f);
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

const int Weapon::getRange() const
{
	return range;
}