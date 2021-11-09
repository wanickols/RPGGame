#include "stdafx.h"
#include "Movement.h"
#include "Entity.h"
#include "AnimationC.h"
#include "PhysicsDevice.h"
#include "Entity.h"
#include "physicsComponent.h"

Movement::Movement(sf::Sprite& sprite, float maxVelocity, float acceleration, float deceleration, Entity& owner)
	: sprite(sprite), maxVelocity(maxVelocity), acceleration(acceleration), deceleration(deceleration), velocity(0.f, 0.f), lastState(0), direction(facing::IDLE),
	Component("movement", owner)
{

}

Movement::~Movement()
{
}

//Accesors
const sf::Vector2f& Movement::getVelocity()
{
	return velocity;
}

const float& Movement::getMaxVelocity() const
{
	return maxVelocity;
}

const bool Movement::getState(const short unsigned state)
{
		

	switch (state)
	{
	case DOWNIDLE:

		if (velocity.x == 0.f && velocity.y == 0.f)
			if (lastState == movement_states::MOVING_DOWN || lastState == movement_states::DOWNIDLE) {
				lastState = state;
				return true;
			}

		break;
	case UPIDLE:

		if (velocity.x == 0.f && velocity.y == 0.f)
			if (lastState == movement_states::MOVING_UP || lastState == movement_states::UPIDLE) {
				lastState = state;
				return true;
			}

		break;
	case LEFTIDLE:

		if (velocity.x == 0.f && velocity.y == 0.f)
			if (lastState == movement_states::MOVING_LEFT || lastState == movement_states::LEFTIDLE) {
				lastState = state;
				return true;
			}

		break;
	case RIGHTIDLE:

		if (velocity.x == 0.f && velocity.y == 0.f)
			if (lastState == movement_states::MOVING_RIGHT || lastState == movement_states::RIGHTIDLE) {
				lastState = state;
				return true;
			}

		break;

	case ATTACK:

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			return true;
		break;

	case MOVING_LEFT:

		if (velocity.x < 0.f) {
			lastState = state;
			return true;
		}

		break;

	case MOVING_RIGHT:

		if (velocity.x > 0.f) {
			lastState = state;
			return true;
		}
		break;

	case MOVING_UP:

		if (velocity.y < 0.f) {
			lastState = state;
			return true;
		}
		break;

	case MOVING_DOWN:

		if (velocity.y > 0.f) {
			lastState = state;
			return true;
		}
		break;
	}

	return false;
}

const unsigned short int Movement::getState()
{	
	if (getState(DOWNIDLE))
	{
		return DOWNIDLE;
	}
	else if (getState(UPIDLE))
	{
		return UPIDLE;
	}
	else if (getState(LEFTIDLE))
	{
		return LEFTIDLE;
	}
	else if (getState(RIGHTIDLE))
	{
		return RIGHTIDLE;
	}
	else if (getState(MOVING_LEFT))
	{
		return MOVING_LEFT;
	}
	else if (getState(MOVING_UP))
	{
		return MOVING_UP;
	}
	else if (getState(MOVING_RIGHT))
	{
		return MOVING_RIGHT;
	}
	else if (getState(MOVING_DOWN))
	{
		return MOVING_DOWN;
	}
	else
		throw("ERROR::Movement::GETSTATE()::DID NOT RETURN ANY STATE ");
	
}

const unsigned short int Movement::getLastState() const
{
	return lastState;
}

const facing Movement::getDirection() const
{
	return direction;
}

void Movement::setDirection(facing player_direction)
{
	direction = player_direction;
}

void Movement::setLastState(const short unsigned state)
{
	lastState = state;
}

void Movement::setAcceleration(float newAccel)
{
	acceleration = newAccel;
}

void Movement::stopVelocity()
{
	/* Resets the velocity to 0.*/

	velocity.x = 0.f;
	velocity.y = 0.f;
}

void Movement::halfVelocity()
{
	velocity.x /= 2;
	velocity.y /= 2;
}

void Movement::stopVelocityX()
{
	/* Resets the velocity x to 0.*/

	velocity.x = 0.f;
}

void Movement::stopVelocityY()
{
	/* Resets the velocity y to 0.*/

	velocity.y = 0.f;
}


//Functions
void Movement::move(const float dir_x, const float dir_y, const float& dt, bool player)
{
		velocity.x += acceleration * dir_x * dt;
		velocity.y += acceleration * dir_y * dt;

}

void Movement::update(const float& dt, const sf::Vector2f mousePosView)
{

	if (velocity.x != 0.f || velocity.y != 0.f) {
		owner.getComponent<physicsComponent>()->pDevice->setVelocity(owner, velocity);
		owner.getComponent<physicsComponent>()->pDevice->findBody(owner)->ApplyForceToCenter({ -velocity.x / 100 , -velocity.y / 100 }, true);
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

	}
	//Final move


}

void Movement::render(sf::RenderTarget& target, sf::Shader* shader, sf::Vector2f light_position, const bool show_hitbox)
{

	
	
	
}
