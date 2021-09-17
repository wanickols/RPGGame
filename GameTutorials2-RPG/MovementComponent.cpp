#include "stdafx.h"
#include "MovementComponent.h"

MovementComponent::MovementComponent(sf::Sprite& sprite, float maxVelocity, float acceleration, float deceleration)
	: sprite(sprite), maxVelocity(maxVelocity), acceleration(acceleration), deceleration(deceleration), velocity(0.f, 0.f)
{
	lastState = 0;
}

MovementComponent::~MovementComponent()
{
}

//Accesors
const sf::Vector2f& MovementComponent::getVelocity()
{
	return velocity;
}

const float& MovementComponent::getMaxVelocity() const
{
	return maxVelocity;
}

const bool MovementComponent::getState(const short unsigned state) const
{
	
	switch (state)
	{
	case DOWNIDLE:

		if (velocity.x == 0.f && velocity.y == 0.f)
			if (lastState == movement_states::MOVING_DOWN || lastState == movement_states::DOWNIDLE) {
				return true;
			}

		break;
	case UPIDLE:

		if (velocity.x == 0.f && velocity.y == 0.f)
			if (lastState == movement_states::MOVING_UP || lastState == movement_states::UPIDLE)
			return true;

		break;
	case LEFTIDLE:

		if (velocity.x == 0.f && velocity.y == 0.f)
			if (lastState == movement_states::MOVING_LEFT || lastState == movement_states::LEFTIDLE)
			return true;

		break;
	case RIGHTIDLE:

		if (velocity.x == 0.f && velocity.y == 0.f)
			if (lastState == movement_states::MOVING_RIGHT || lastState == movement_states::RIGHTIDLE)
			return true;

		break;

	case ATTACK:

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			return true;
		break;

	case MOVING_LEFT:

		if (velocity.x < 0.f)
			return true;

		break;

	case MOVING_RIGHT:

		if (velocity.x > 0.f)
			return true;

		break;

	case MOVING_UP:

		if (velocity.y < 0.f)
			return true;

		break;

	case MOVING_DOWN:

		if (velocity.y > 0.f)
			return true;

		break;
	}

	return false;
}

const unsigned short int MovementComponent::getLastState() const
{
	return lastState;
}

void MovementComponent::setLastState(const short unsigned state)
{
	lastState = state;
}

void MovementComponent::stopVelocity()
{
	/* Resets the velocity to 0.*/

	velocity.x = 0.f;
	velocity.y = 0.f;
}

void MovementComponent::stopVelocityX()
{
	/* Resets the velocity x to 0.*/

	velocity.x = 0.f;
}

void MovementComponent::stopVelocityY()
{
	/* Resets the velocity y to 0.*/

	velocity.y = 0.f;
}


//Functions
void MovementComponent::move(const float dir_x, const float dir_y, const float& dt)
{
	//Acceleration
	velocity.x += acceleration * dir_x * dt;
	velocity.y += acceleration * dir_y * dt;

}

void MovementComponent::update(const float& dt)
{
	/*X MOVEMENT*/
	if (velocity.x > 0.f) { //positive x movement
		//maxVelocity check x
		if (velocity.x > maxVelocity)
			velocity.x = maxVelocity;

		//DECELERATION X
		velocity.x -= deceleration * dt;
		if (velocity.x < 0.f)
			velocity.x = 0;
	}
	else if (velocity.x < 0.f) { //negative x movement

		//Max velocity check x
		if (velocity.x < -maxVelocity)
			velocity.x = -maxVelocity;

		//DECELERATION X
		velocity.x += deceleration * dt;
		if (velocity.x > 0.f)
			velocity.x = 0;
	}
	/*Y MOVEMENT*/
	if (velocity.y > 0.f) { //positive y movement
		//maxVelocity check y
		if (velocity.y > maxVelocity)
			velocity.y = maxVelocity;

		//DECELERATION Y
		velocity.y -= deceleration * dt;
		if (velocity.y < 0.f)
			velocity.y = 0;
	}
	else if (velocity.y < 0.f) { //negative y movement

	   //Max velocity check y
		if (velocity.y < -maxVelocity)
			velocity.y = -maxVelocity;

		//DECELERATION Y
		velocity.y += deceleration * dt;
		if (velocity.y > 0.f)
			velocity.y = 0;
	}

	//Final move
	sprite.move(velocity * dt); //uses velocity	
}
