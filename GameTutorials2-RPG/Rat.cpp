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
	


}

void Rat::initAnimations(sf::Texture& texture_sheet, float x, float y)
{
	//Animation
	std::shared_ptr<AnimationC> animation = std::make_shared<AnimationC>(sprite, texture_sheet, x, y, this);
	addComponent(animation);

	/*getComponent<AnimationC>()->addAnimation("DOWNIDLE", 10.f, 0, 0, 3, 0, 60, 64);
	getComponent<AnimationC>()->addAnimation("WALKRIGHT", 10.f, 0, 1, 3, 1, 60, 64);
	getComponent<AnimationC>()->addAnimation("WALKLEFT", 10.f, 0, 2, 3, 2, 60, 64);
	getComponent<AnimationC>()->addAnimation("WALKUP", 10.f, 0, 3, 3, 3, 60, 64);
	getComponent<AnimationC>()->addAnimation("WALKDOWN", 10.f, 0, 4, 3, 4, 60, 64);*/
	//getComponent<AnimationC>()->addAnimation("ATTACK", 10.f, 0, 0, 3, 0, 60, 64); //doesn't exist
}

Rat::Rat(float x, float y, sf::Texture& texture, EnemySpawner& origin)
	: Enemy(x ,y, texture, origin)
{
	initVariables();
	initAnimations(texture, x, y);
	initComponents(origin);
	
}

void Rat::updateAnimation(const float& dt)
{
	//Ai FIXME (make AI component
	
}

void Rat::update(const float& dt, const sf::Vector2f mousePosView)
{
	Entity::update(dt, mousePosView);
	//debugging
	//getComponent<Movement>()->move(0.f, 0.f, dt, false);
	
	//getComponent<Attribute>()->loseHealth(1);
	updateAnimation(dt);
}

void Rat::render(sf::RenderTarget& target, sf::Shader* shader, sf::Vector2f light_position, const bool show_hitbox)
{
	//Goal of components!
	Entity::render(target, shader, light_position, false);
}
