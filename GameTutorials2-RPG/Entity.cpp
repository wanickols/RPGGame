#include "stdafx.h"
#include "Entity.h"

void Entity::initVariables()
{
	this->hitBoxComponent = NULL;
	this->movementComponent = NULL;
	this->animationComponent = NULL;
}

Entity::Entity()
{

	this->initVariables();
}

Entity::~Entity()
{

}

//Component functions
void Entity::setTexture(sf::Texture& texture)
{
	//this->texture = std::make_unique<sf::Texture>(&texture);
	this->sprite.setTexture(texture);
}

void Entity::createMovementComponent(const float maxVelocity, const float acceleration, const float deceleration)
{
	this->movementComponent = std::make_unique<MovementComponent>(this->sprite, maxVelocity, acceleration, deceleration);
}

void Entity::createAnimationComponent(sf::Texture& texture_sheet)
{
	this->animationComponent = std::make_unique<AnimationComponent>(this->sprite, texture_sheet);
}

void Entity::createHitBoxComponent(sf::Sprite& sprite, const float offset_x, const float offset_y, float width, float height)
{
	this->hitBoxComponent = std::make_unique<HitboxComponent>(sprite, offset_x, offset_y, width, height);
}

//Accessors
const sf::Vector2f Entity::getPosition() const
{
	if (this->hitBoxComponent)
		return this->hitBoxComponent->getPosition();

	return this->sprite.getPosition();
}

//functions
void Entity::setPosition(float x, float y)
{
	if (this->hitBoxComponent)
		this->hitBoxComponent->setPosition(sf::Vector2f(x, y));
	else
		this->sprite.setPosition(x, y);

}

void Entity::move(const float dir_x, const float dir_y, const float& dt)
{
	if (this->movementComponent) {
		this->movementComponent->move(dir_x, dir_y, dt); //setsVelocity
	}
}

const sf::FloatRect Entity::getGlobalBounds() const
{
	if (this->hitBoxComponent)
		return this->hitBoxComponent->getGlobalBounds();

	return this->sprite.getGlobalBounds();
}

void Entity::stopVelocity()
{
	if (this->movementComponent)
		this->movementComponent->stopVelocity();
}

void Entity::stopVelocityX()
{
	if (this->movementComponent)
		this->movementComponent->stopVelocityX();
}

void Entity::stopVelocityY()
{
	if (this->movementComponent)
		this->movementComponent->stopVelocityY();
}


