#include "stdafx.h"
#include "Enemy.h"
#include "EnemySpawner.h"
#include "Item.h"

void Enemy::initVariables()
{
	name = "NoNameEnemy";
}
void Enemy::initComponents()
{
	createMovementComponent(350.f, 1300.f, 400.f); //speed for enemy set here
	createHitBoxComponent(sprite, 12.f, 4.f, 41, 60);
	creatAttributeComponent(1); //<aybe later
}

void Enemy::initAnimations(sf::Texture& texture_sheet)
{
	createAnimationComponent(texture_sheet);
	animationComponent->addAnimation("DOWNIDLE", 15.f, 0, 0, 4, 0, 64, 64);
}

Enemy::Enemy(float x, float y, sf::Texture& texture_sheet, EnemySpawner& origin)
{
	initVariables();
	initComponents();
	initAnimations(texture_sheet);
	Origin = std::make_unique<EnemySpawner>(origin);

	setPosition(x, y);

}

Enemy::~Enemy()
{
}

void Enemy::updateAnimation(const float& dt)
{
	animationComponent->play("DOWNIDLE", dt, false);
}

void Enemy::update(const float& dt, const sf::Vector2f mousePosView)
{

	movementComponent->update(dt);

	updateAnimation(dt);

	hitBoxComponent->update();

}

void Enemy::render(sf::RenderTarget& target, sf::Shader* shader, sf::Vector2f light_position, const bool show_hitbox)
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