#include "stdafx.h"
#include "Rat.h"
#include "MovementComponent.h"
#include "AnimationComponent.h"
#include "AttributeComponent.h"
#include "HitboxComponent.h"

void Rat::initVariables()
{
	name = "Rat";
	expWorth = 100;
	//dropItem
}

void Rat::initComponents()
{
	//Movement
	std::shared_ptr<MovementComponent> movementComponent = std::make_shared<MovementComponent>(sprite, 350.f, 1300.f, 400.f, this); //speed for rat set here
	addComponent(movementComponent);

	//Hitbox
	std::shared_ptr<HitboxComponent> hitboxComponent = std::make_shared<HitboxComponent>(sprite, 20.f, 32.f, 16.f, 16.f, this); //hitbox for player set here
	addComponent(hitboxComponent);

	//attribute
	std::shared_ptr<AttributeComponent> attributeComponent = std::make_shared<AttributeComponent>(1, this); //hitbox for player set here
	addComponent(attributeComponent);
}

void Rat::initAnimations(sf::Texture& texture_sheet)
{
	//Animation
	std::shared_ptr<AnimationComponent> animationComponent = std::make_shared<AnimationComponent>(sprite, texture_sheet, this);
	addComponent(animationComponent);

	getComponent<AnimationComponent>()->addAnimation("DOWNIDLE", 10.f, 0, 0, 3, 0, 60, 64);
	getComponent<AnimationComponent>()->addAnimation("WALKRIGHT", 10.f, 0, 1, 3, 1, 60, 64);
	getComponent<AnimationComponent>()->addAnimation("WALKLEFT", 10.f, 0, 2, 3, 2, 60, 64);
	getComponent<AnimationComponent>()->addAnimation("WALKUP", 10.f, 0, 3, 3, 3, 60, 64);
	getComponent<AnimationComponent>()->addAnimation("WALKDOWN", 10.f, 0, 4, 3, 4, 60, 64);
	//getComponent<AnimationComponent>()->addAnimation("ATTACK", 10.f, 0, 0, 3, 0, 60, 64); //doesn't exist
}

Rat::Rat(float x, float y, sf::Texture& texture, EnemySpawner& origin)
	: Enemy(x, y, texture, origin)
{
	sprite.setTexture(texture);
	sprite.setTextureRect(sf::IntRect(0, 0, 32, 32));
	setPosition(x, y);
	initVariables();
	initComponents();
	initAnimations(texture);
}

void Rat::updateAnimation(const float& dt)
{
	//getComponent<AnimationComponent>()->play("DOWNIDLE", dt, false);
	if(getComponent<MovementComponent>()->getDirection() == facing::RIGHT)
	{
		getComponent<AnimationComponent>()->play("WALKRIGHT", dt, false);
	}
}

void Rat::update(const float& dt, const sf::Vector2f mousePosView)
{
	Entity::update(dt, mousePosView);
	getComponent<MovementComponent>()->move(.4f, 0.f, dt, false);
	getComponent<MovementComponent>()->setDirection(facing::RIGHT);

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
