#include "stdafx.h"
#include "Player.h"

//Init Functions
void Player::initVariables()
{
	attacking = false;
}

void Player::initComponents()
{
	this->createMovementComponent(350.f, 1300.f, 400.f); //speed for player set here
	this->createHitBoxComponent(this->sprite, 12.f, 4.f, 41, 60);
}

//Constructors
Player::Player(float x, float y, sf::Texture& texture_sheet)
{
	this->initVariables();
	this->initComponents();

	this->setPosition(x, y);

	this->createAnimationComponent(texture_sheet);
	this->animationComponent->addAnimation("IDLE", 15.f, 0, 0, 8, 0, 64, 64);
	this->animationComponent->addAnimation("WALK_DOWN", 8.f, 0, 1, 3, 1, 64, 64);
	this->animationComponent->addAnimation("WALK_LEFT", 8.f, 4, 1, 7, 1, 64, 64);
	this->animationComponent->addAnimation("WALK_RIGHT", 8.f, 8, 1, 11, 1, 64, 64);
	this->animationComponent->addAnimation("WALK_UP", 8.f, 12, 1, 15, 1, 64, 64);
	this->animationComponent->addAnimation("ATTACK", 6.f, 0, 1, 8, 1, 64, 128);
}

Player::~Player()
{

}

//Functions
void Player::updateAnimation(const float& dt)
{
	if (this->movementComponent->getState(ATTACK)) {
		attacking = true;
		if (attacking) {
			if (this->animationComponent->play("ATTACK", dt, false))
				attacking = false;
		}
	}
	else {

		if (this->movementComponent->getState(IDLE))
		{
			this->animationComponent->play("IDLE", dt, false);
		}
		else if (this->movementComponent->getState(MOVING_LEFT))
		{
			this->animationComponent->play("WALK_LEFT", dt, this->movementComponent->getVelocity().x, this->movementComponent->getMaxVelocity(), false);
		}
		else if (this->movementComponent->getState(MOVING_RIGHT))
		{
			this->animationComponent->play("WALK_RIGHT", dt, this->movementComponent->getVelocity().x, this->movementComponent->getMaxVelocity(), false);
		}
		else if (this->movementComponent->getState(MOVING_UP))
		{
			this->animationComponent->play("WALK_UP", dt, this->movementComponent->getVelocity().y, this->movementComponent->getMaxVelocity(), false);
		}
		else if (this->movementComponent->getState(MOVING_DOWN))
		{
			this->animationComponent->play("WALK_DOWN", dt, this->movementComponent->getVelocity().y, this->movementComponent->getMaxVelocity(), false);
		}
	}
}

void Player::update(const float& dt)
{

	this->movementComponent->update(dt);
	this->updateAnimation(dt);
	this->hitBoxComponent->update();

}

void Player::render(sf::RenderTarget& target)
{
	target.draw(this->sprite);
	this->hitBoxComponent->render(target);

}



