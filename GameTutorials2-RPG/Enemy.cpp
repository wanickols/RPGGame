#include "stdafx.h"
#include "Enemy.h"
#include "Item.h"

void Enemy::initVariables()
{


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

Enemy::Enemy(float x, float y, sf::Texture& texture_sheet)
{
	initVariables();
	initComponents();
	initAnimations(texture_sheet);

	setPosition(x, y);

}

Enemy::~Enemy()
{
}

void Enemy::updateAnimation(const float& dt, const sf::Vector2f& mousePosView)
{
	animationComponent->play("DOWNIDLE", dt, false);
}

void Enemy::update(const float& dt, const sf::Vector2f& mousePosView)
{

	movementComponent->update(dt);
	//activeRune->update(dt, mousePosView);
	//Bullets
	//Checks if there are bullets on the screen to know if keep arms up or put them down
	/*if (activeRune->isBulletEmpty()) {
		animationComponent->setIsDone("IDLEATTACKDOWN", false);
		animationComponent->setIsDone("IDLEATTACKUP", false);
		animationComponent->setIsDone("IDLEATTACKLEFT", false);
		animationComponent->setIsDone("IDLEATTACKRIGHT", false);
	}*/

	updateAnimation(dt, mousePosView);

	hitBoxComponent->update();

	//std::cout << skillComponent->getSkillLvl("Endurance") << "\n";


	//addExp(20);
	//system("cls");
	//std::cout << attributeComponent->debugPrint();

}

void Enemy::render(sf::RenderTarget& target, sf::Shader* shader, const bool show_hitbox)
{
	if (shader) {
		shader->setUniform("hasTexture", true);
		shader->setUniform("lightPos", this->getCenterPosition());

		target.draw(sprite, shader);
		//activeRune->render(target, shader);
	}
	else {
		target.draw(sprite);
		//activeRune->render(target);
	}
	if (show_hitbox)
		hitBoxComponent->render(target);

}