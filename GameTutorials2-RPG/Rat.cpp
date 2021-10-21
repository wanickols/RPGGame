#include "stdafx.h"
#include "Rat.h"
#include "Movement.h"
#include "AnimationC.h"
#include "Attribute.h"
#include "Hitbox.h"
#include "EnemyData.h"
#include "FireRune.h"

void Rat::initVariables()
{
	//dropItem
}

void Rat::initComponents(EnemySpawner& origin)
{
	//Movement
	std::shared_ptr<Movement> movement = std::make_shared<Movement>(sprite, 350.f, 1300.f, 400.f, this); //speed for enemy set here
	addComponent(movement);

	//Hitbox
	std::shared_ptr<Hitbox> hitbox = std::make_shared<Hitbox>(sprite, 20.f, 32.f, 16.f, 16.f, this); //hitbox for enemy set here
	addComponent(hitbox);

	//attribute
	std::shared_ptr<Attribute> attribute = std::make_shared<Attribute>(1, this); //attribute for enemy set here
	addComponent(attribute);

	std::shared_ptr<EnemyData> data = std::make_shared<EnemyData>("Rat", 100, nullptr, origin, this); //data for enemy set here
	addComponent(data);


}

void Rat::initAnimations(sf::Texture& texture_sheet, float x, float y)
{
	//Animation
	std::shared_ptr<AnimationC> animation = std::make_shared<AnimationC>(sprite, texture_sheet, x, y, this);
	addComponent(animation);

	getComponent<AnimationC>()->addAnimation("DOWNIDLE", 10.f, 0, 0, 3, 0, 60, 64);
	getComponent<AnimationC>()->addAnimation("WALKRIGHT", 10.f, 0, 1, 3, 1, 60, 64);
	getComponent<AnimationC>()->addAnimation("WALKLEFT", 10.f, 0, 2, 3, 2, 60, 64);
	getComponent<AnimationC>()->addAnimation("WALKUP", 10.f, 0, 3, 3, 3, 60, 64);
	getComponent<AnimationC>()->addAnimation("WALKDOWN", 10.f, 0, 4, 3, 4, 60, 64);
	//getComponent<AnimationC>()->addAnimation("ATTACK", 10.f, 0, 0, 3, 0, 60, 64); //doesn't exist
}

Rat::Rat(float x, float y, sf::Texture& texture, EnemySpawner& origin)
{
	initVariables();
	initAnimations(texture, x, y);
	initComponents(origin);
	
}

void Rat::updateAnimation(const float& dt)
{
	//Ai FIXME (make AI component
	if(getComponent<Movement>()->getDirection() == facing::RIGHT)
	{
		getComponent<AnimationC>()->play("WALKRIGHT", dt, false);
	}
}

void Rat::update(const float& dt, const sf::Vector2f mousePosView)
{
	Entity::update(dt, mousePosView);
	//debugging
	getComponent<Movement>()->move(0.f, 0.f, dt, false);
	getComponent<Movement>()->setDirection(facing::RIGHT);
	getComponent<Attribute>()->loseHealth(1);
	updateAnimation(dt);
}

void Rat::render(sf::RenderTarget& target, sf::Shader* shader, sf::Vector2f light_position, const bool show_hitbox)
{
	//Goal of components!
	Entity::render(target, shader, light_position, false);
}
