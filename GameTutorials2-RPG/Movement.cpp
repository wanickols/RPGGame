#include "stdafx.h"
#include "Movement.h"
#include "Entity.h"
#include "AnimationC.h"
#include "PhysicsDevice.h"
#include "Entity.h"
#include "physicsComponent.h"
#include "Attribute.h"

Movement::Movement(sf::Sprite& sprite, sf::Vector2f maxVelocity, sf::Vector2f acceleration, sf::Vector2f deceleration, Entity& owner)
	: sprite(sprite), maxVelocity(maxVelocity), acceleration(acceleration), deceleration(deceleration), velocity(0.f, 0.f), direction(facing::DOWN), MOVING(false),
	Component("movement", owner)
{
	pDevice = owner.getComponent<physicsComponent>()->pDevice;
}

Movement::~Movement()
{
}

//Accessors
const sf::Vector2f& Movement::getMaxVelocity() const
{
	return maxVelocity;
}

const facing Movement::getDirection() const
{
	return direction;
}

const bool Movement::getMOVING()
{
	return MOVING;
}

void Movement::setMOVING(const bool moving)
{
	MOVING = moving;
}

void Movement::setDirection(facing player_direction)
{
	direction = player_direction;
}

void Movement::setAcceleration(sf::Vector2f deceleration)
{
	acceleration.x /= 2.f;
	acceleration.y /= 2.f;
}

void Movement::decelerate(sf::Vector2f newAccel)
{

}

void Movement::setAcceleration(sf::Vector2f& newAccel)
{
	acceleration = newAccel;
}

void Movement::setAcceleration(float accelX, float accelY)
{
	acceleration.x = accelX;
	acceleration.y = accelY;
}

void Movement::stopVelocity()
{

}

void Movement::halfVelocity()
{

}

void Movement::stopVelocityX()
{

}
void Movement::stopVelocityY()
{
}


//Functions
void Movement::move(const float dir_x, const float dir_y, const float& dt, bool bullet)
{
	MOVING = true;
	if(bullet)
	{
		velocity.x = dir_x * acceleration.x;
		velocity.y = dir_y * acceleration.y;
	}
	else {
		if (dir_x != 0)
		{
			velocity.x += dir_x * acceleration.x;
			velocity.y /= deceleration.x;
		}
		else if (dir_y != 0) {
			velocity.x /= deceleration.y;
			velocity.y += dir_y * acceleration.y;
		}
		
	}
	owner.getComponent<physicsComponent>()->pDevice->setVelocity(owner, velocity);
}

void Movement::update(const float& dt, const sf::Vector2f mousePosView)
{
	if (MOVING)
	{
		
		if (pDevice->findBody(owner)->GetLinearVelocity().Length() < 1.4f) {
			MOVING = false;
		//pDevice->findBody(owner)->SetLinearVelocity(b2Vec2(0.f, 0.f));
		} 
	}

	velocity.x /= deceleration.x;
	velocity.y /= deceleration.y;
	//std::cout << "LENGTH OF " << owner.getComponent<Attribute>()->EntityName << ": " << pDevice->findBody(owner)->GetLinearVelocity().Length() << "\n";
}

void Movement::render(sf::RenderTarget& target, sf::Shader* shader, sf::Vector2f light_position, const bool show_hitbox)
{
	
}
