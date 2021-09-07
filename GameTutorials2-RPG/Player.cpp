#include "stdafx.h"
#include "Player.h"

//Init Functions
void Player::initVariables()
{
	attacking = false;
}

void Player::initComponents()
{
	createMovementComponent(350.f, 1300.f, 400.f); //speed for player set here
	createHitBoxComponent(sprite, 12.f, 4.f, 41, 60);
}

//Constructors
Player::Player(float x, float y, sf::Texture& texture_sheet)
{
	initVariables();
	initComponents();

	setPosition(x, y);

	createAnimationComponent(texture_sheet);
	creatAttributeComponent(1);
	animationComponent->addAnimation("IDLE", 15.f, 0, 0, 8, 0, 64, 64);
	animationComponent->addAnimation("WALK_DOWN", 8.f, 0, 1, 3, 1, 64, 64);
	animationComponent->addAnimation("WALK_LEFT", 8.f, 4, 1, 7, 1, 64, 64);
	animationComponent->addAnimation("WALK_RIGHT", 8.f, 8, 1, 11, 1, 64, 64);
	animationComponent->addAnimation("WALK_UP", 8.f, 12, 1, 15, 1, 64, 64);
	animationComponent->addAnimation("ATTACK", 6.f, 0, 1, 8, 1, 64, 128);

	
}

Player::~Player()
{

}

std::shared_ptr<AttributeComponent> Player::getAttributeComponent()
{
	return attributeComponent;
}

void Player::loseHealth(const int health)
{
	attributeComponent->hp -= health;
	attributeComponent->healthUpdate = true;
	if (attributeComponent->hp < 0)
		attributeComponent->hp = 0;
}

void Player::addHealth(const int health)
{
	attributeComponent->hp += health;
	attributeComponent->healthUpdate = true;
	if (attributeComponent->hp > attributeComponent->hpMax)
		attributeComponent->hp = attributeComponent->hpMax;
}

void Player::loseEnergy(const int energy)
{
	attributeComponent->energy -= energy;
	attributeComponent->energyUpdate = true;
	if (attributeComponent->energy < 0)
		attributeComponent->energy = 0;
}

void Player::addEnergy(const int energy)
{
	attributeComponent->energy += energy;
	attributeComponent->energyUpdate = true;
	if (attributeComponent->energy > attributeComponent->energyMax)
		attributeComponent->energy = attributeComponent->energyMax;
}

void Player::loseExp(const int exp)
{
	attributeComponent->exp -= exp;
	if (attributeComponent->exp < 0)
		attributeComponent->exp = 0;
}

void Player::addExp(const int exp)
{
	attributeComponent->addExp(exp);
}

//Functions
void Player::updateAnimation(const float& dt)
{
	if (movementComponent->getState(ATTACK)) {
		attacking = true;
		if (attacking) {
			if (animationComponent->play("ATTACK", dt, false))
				attacking = false;
		}
	}
	else {

		if (movementComponent->getState(IDLE))
		{
			animationComponent->play("IDLE", dt, false);
		}
		else if (movementComponent->getState(MOVING_LEFT))
		{
			animationComponent->play("WALK_LEFT", dt, movementComponent->getVelocity().x, movementComponent->getMaxVelocity(), false);
		}
		else if (movementComponent->getState(MOVING_RIGHT))
		{
			animationComponent->play("WALK_RIGHT", dt, movementComponent->getVelocity().x, movementComponent->getMaxVelocity(), false);
		}
		else if (movementComponent->getState(MOVING_UP))
		{
			animationComponent->play("WALK_UP", dt, movementComponent->getVelocity().y, movementComponent->getMaxVelocity(), false);
		}
		else if (movementComponent->getState(MOVING_DOWN))
		{
			animationComponent->play("WALK_DOWN", dt, movementComponent->getVelocity().y, movementComponent->getMaxVelocity(), false);
		}
	}
}

void Player::update(const float& dt)
{
	movementComponent->update(dt);
	
	updateAnimation(dt);
	
	hitBoxComponent->update();
	
	
	//addExp(20);
	//system("cls");
	//std::cout << attributeComponent->debugPrint();
	
}

void Player::render(sf::RenderTarget& target, sf::Shader* shader, const bool show_hitbox)
{
	if (shader) {
		shader->setUniform("hasTexture", true);
		shader->setUniform("lightPos", this->getCenterPosition());

		target.draw(sprite, shader);
	}
	else
		target.draw(sprite);
	if(show_hitbox)
		hitBoxComponent->render(target);

}



