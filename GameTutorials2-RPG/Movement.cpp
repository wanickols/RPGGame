#include "stdafx.h"
#include "Movement.h"
#include "Entity.h"
#include "AnimationC.h"
#include "PhysicsDevice.h"
#include "Entity.h"
#include "physicsComponent.h"
#include "Attribute.h"

Movement::Movement(sf::Sprite& sprite, float maxVelocity, float acceleration, float deceleration, Entity& owner)
	: sprite(sprite), maxVelocity(maxVelocity), acceleration(acceleration), deceleration(deceleration), velocity(0.f, 0.f), direction(facing::DOWN), MOVING(false),
	Component("movement", owner)
{
	pDevice = owner.getComponent<physicsComponent>()->pDevice;
}

Movement::~Movement()
{
}

//Accessors
const float& Movement::getMaxVelocity() const
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

void Movement::setAcceleration(float newAccel)
{
	acceleration = newAccel;
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
void Movement::move(const float dir_x, const float dir_y, const float& dt, bool player)
{
	MOVING = true;
	sf::Vector2f velocity(dir_x * acceleration, dir_y * acceleration);
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
	std::cout << "LENGTH OF " << owner.getComponent<Attribute>()->EntityName << ": " << pDevice->findBody(owner)->GetLinearVelocity().Length() << "\n";
}

void Movement::render(sf::RenderTarget& target, sf::Shader* shader, sf::Vector2f light_position, const bool show_hitbox)
{

	
	
	
}
