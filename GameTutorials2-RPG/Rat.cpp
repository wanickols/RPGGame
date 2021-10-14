#include "stdafx.h"
#include "Rat.h"
#include "Movement.h"
#include "AnimationC.h"
#include "Attribute.h"
#include "Hitbox.h"

void Rat::initVariables()
{
	name = "Rat";
	expWorth = 100;
	//dropItem
}

void Rat::initComponents()
{
	//Movement
	std::shared_ptr<Movement> movement = std::make_shared<Movement>(sprite, 350.f, 1300.f, 400.f, this); //speed for rat set here
	addComponent(movement);

	//Hitbox
	std::shared_ptr<Hitbox> hitbox = std::make_shared<Hitbox>(sprite, 20.f, 32.f, 16.f, 16.f, this); //hitbox for player set here
	addComponent(hitbox);

	//attribute
	std::shared_ptr<Attribute> attribute = std::make_shared<Attribute>(1, this); //hitbox for player set here
	addComponent(attribute);
}

void Rat::initAnimations(sf::Texture& texture_sheet)
{
	//Animation
	std::shared_ptr<AnimationC> animation = std::make_shared<AnimationC>(sprite, texture_sheet, this);
	addComponent(animation);

	getComponent<AnimationC>()->addAnimation("DOWNIDLE", 10.f, 0, 0, 3, 0, 60, 64);
	getComponent<AnimationC>()->addAnimation("WALKRIGHT", 10.f, 0, 1, 3, 1, 60, 64);
	getComponent<AnimationC>()->addAnimation("WALKLEFT", 10.f, 0, 2, 3, 2, 60, 64);
	getComponent<AnimationC>()->addAnimation("WALKUP", 10.f, 0, 3, 3, 3, 60, 64);
	getComponent<AnimationC>()->addAnimation("WALKDOWN", 10.f, 0, 4, 3, 4, 60, 64);
	//getComponent<AnimationC>()->addAnimation("ATTACK", 10.f, 0, 0, 3, 0, 60, 64); //doesn't exist
}

Rat::Rat(float x, float y, sf::Texture& texture, EnemySpawner& origin)
	: Enemy(x, y, texture, origin)
{
	sprite.setTexture(texture);
	sprite.setTextureRect(sf::IntRect(0, 0, 32, 32));
	setPosition(x, y);
	initVariables();
	initAnimations(texture);
	initComponents();
	
}

void Rat::updateAnimation(const float& dt)
{
	//getComponent<AnimationC>()->play("DOWNIDLE", dt, false);
	if(getComponent<Movement>()->getDirection() == facing::RIGHT)
	{
		getComponent<AnimationC>()->play("WALKRIGHT", dt, false);
	}
}

void Rat::update(const float& dt, const sf::Vector2f mousePosView)
{
	Entity::update(dt, mousePosView);
	//debugging
	getComponent<Movement>()->move(.4f, 0.f, dt, false);
	getComponent<Movement>()->setDirection(facing::RIGHT);

	updateAnimation(dt);
}

void Rat::render(sf::RenderTarget& target, sf::Shader* shader, sf::Vector2f light_position, const bool show_hitbox)
{
	if (shader) {
		shader->setUniform("hasTexture", true);
		shader->setUniform("lightPos", light_position);

		target.draw(sprite, shader);
	}
	else {
		target.draw(sprite);
	}

}
