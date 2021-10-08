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
	createHitBoxComponent(sprite, 12.f, 4.f, 41, 60);
	creatAttributeComponent(1); //<aybe later
}

void Rat::initAnimations(sf::Texture& texture_sheet)
{
	createAnimationComponent(texture_sheet);
	animationComponent->addAnimation("DOWNIDLE", 15.f, 0, 0, 4, 0, 64, 64);
}

Rat::Rat(float x, float y, sf::Texture& texture, EnemySpawner& origin)
	: Enemy(x, y, texture, origin)
{
	initVariables();
	initComponents();
	initAnimations(texture);
}

void Rat::updateAnimation(const float& dt)
{
	animationComponent->play("DOWNIDLE", dt, false);
	
}

void Rat::update(const float& dt, const sf::Vector2f mousePosView)
{
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
	if (show_hitbox)
		hitBoxComponent->render(target);

}
