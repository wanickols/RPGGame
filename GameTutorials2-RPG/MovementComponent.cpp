#include "stdafx.h"
#include "MovementComponent.h"

MovementComponent::MovementComponent(sf::Sprite& sprite, float maxVelocity, float acceleration, float deceleration)
	: sprite(sprite), maxVelocity(maxVelocity), acceleration(acceleration), deceleration(deceleration), velocity(0.f, 0.f)
{
}

MovementComponent::~MovementComponent()
{
}

//Accesors
const sf::Vector2f& MovementComponent::getVelocity()
{
	return this->velocity;
}

const float& MovementComponent::getMaxVelocity() const
{
	return this->maxVelocity;
}

const bool MovementComponent::getState(const short unsigned state) const
{
	switch (state)
	{
	case IDLE:

		if (this->velocity.x == 0.f && this->velocity.y == 0.f)
			return true;

		break;

	case ATTACK:

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			return true;
		break;

	case MOVING_LEFT:

		if (this->velocity.x < 0.f)
			return true;

		break;

	case MOVING_RIGHT:

		if (this->velocity.x > 0.f)
			return true;

		break;

	case MOVING_UP:

		if (this->velocity.y < 0.f)
			return true;

		break;

	case MOVING_DOWN:

		if (this->velocity.y > 0.f)
			return true;

		break;
	}

	return false;
}

void MovementComponent::stopVelocity()
{
	/* Resets the velocity to 0.*/

	this->velocity.x = 0.f;
	this->velocity.y = 0.f;
}

void MovementComponent::stopVelocityX()
{
	/* Resets the velocity x to 0.*/

	this->velocity.x = 0.f;
}

void MovementComponent::stopVelocityY()
{
	/* Resets the velocity y to 0.*/

	this->velocity.y = 0.f;
}


//Functions
void MovementComponent::move(const float dir_x, const float dir_y, const float& dt)
{
	//Acceleration
	this->velocity.x += this->acceleration * dir_x * dt;
	this->velocity.y += this->acceleration * dir_y * dt;

}

void MovementComponent::update(const float& dt)
{
	/*X MOVEMENT*/
	if (this->velocity.x > 0.f) { //positive x movement
		//maxVelocity check x
		if (this->velocity.x > this->maxVelocity)
			this->velocity.x = maxVelocity;

		//DECELERATION X
		this->velocity.x -= deceleration * dt;
		if (this->velocity.x < 0.f)
			velocity.x = 0;
	}
	else if (this->velocity.x < 0.f) { //negative x movement

		//Max velocity check x
		if (this->velocity.x < -this->maxVelocity)
			this->velocity.x = -maxVelocity;

		//DECELERATION X
		this->velocity.x += deceleration * dt;
		if (this->velocity.x > 0.f)
			velocity.x = 0;
	}
	/*Y MOVEMENT*/
	if (this->velocity.y > 0.f) { //positive y movement
		//maxVelocity check y
		if (this->velocity.y > this->maxVelocity)
			this->velocity.y = maxVelocity;

		//DECELERATION Y
		this->velocity.y -= deceleration * dt;
		if (this->velocity.y < 0.f)
			velocity.y = 0;
	}
	else if (this->velocity.y < 0.f) { //negative y movement

	   //Max velocity check y
		if (this->velocity.y < -this->maxVelocity)
			this->velocity.y = -maxVelocity;

		//DECELERATION Y
		this->velocity.y += deceleration * dt;
		if (this->velocity.y > 0.f)
			velocity.y = 0;
	}

	//Final move
	this->sprite.move(this->velocity * dt); //uses velocity	
}
