#include "stdafx.h"
#include "Rat.h"

void Rat::initVariables()
{
	name = "Rat";
	expWorth = 100;
	//dropItem
}

void Rat::initComponents()
{
	createMovementComponent(350.f, 1300.f, 400.f); //speed for enemy set here
	createHitBoxComponent(sprite, 20.f, 32.f, 16, 16);
	creatAttributeComponent(1); //<aybe later
}

void Rat::initAnimations(sf::Texture& texture_sheet)
{
	createAnimationComponent(texture_sheet);
	animationComponent->addAnimation("DOWNIDLE", 10.f, 0, 0, 3, 0, 60, 64);
	animationComponent->addAnimation("WALKRIGHT", 10.f, 0, 1, 3, 1, 60, 64);
	animationComponent->addAnimation("WALKLEFT", 10.f, 0, 2, 3, 2, 60, 64);
	animationComponent->addAnimation("WALKUP", 10.f, 0, 3, 3, 3, 60, 64);
	animationComponent->addAnimation("WALKDOWN", 10.f, 0, 4, 3, 4, 60, 64);
	//animationComponent->addAnimation("ATTACK", 10.f, 0, 0, 3, 0, 60, 64); //doesn't exist
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
	//animationComponent->play("DOWNIDLE", dt, false);
	if(movementComponent->getDirection() == facing::RIGHT)
	{
		animationComponent->play("WALKRIGHT", dt, false);
	}
}

void Rat::update(const float& dt, const sf::Vector2f mousePosView)
{
	movementComponent->move(.4f, 0.f, dt, false);
	movementComponent->setDirection(facing::RIGHT);
	movementComponent->update(dt);

	updateAnimation(dt);

	hitBoxComponent->update();
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
	//if (show_hitbox)
		hitBoxComponent->render(target);

}
