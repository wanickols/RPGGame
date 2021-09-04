#include "stdafx.h"
#include "Entity.h"

void Entity::initVariables()
{
	this->hitBoxComponent = NULL;
	this->movementComponent = NULL;
	this->animationComponent = NULL;
	this->attributeComponent = NULL;
	
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

void Entity::creatAttributeComponent(int level)
{
	this->attributeComponent = std::make_shared<AttributeComponent>(level);
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

const sf::Vector2i Entity::getGridPosition(const int& gridSizeI)
{
	if (this->hitBoxComponent) {
		gridPosition.x = (int)this->hitBoxComponent->getPosition().x;
		gridPosition.y = (int)this->hitBoxComponent->getPosition().y;

		this->gridPosition.x = this->gridPosition.x / gridSizeI;
		this->gridPosition.y = this->gridPosition.y / gridSizeI;

		return this->gridPosition;
	}


	return sf::Vector2i(
		(int)this->sprite.getPosition().x / gridSizeI,
		(int)this->sprite.getPosition().y / gridSizeI
	);
}

const sf::FloatRect& Entity::getNextPositionBounds(const float& dt) const
{
	if (this->hitBoxComponent && this->movementComponent)
		return this->hitBoxComponent->getNextPosition(this->movementComponent->getVelocity() * dt);

	std::cout << "ENTITY::ERROR IN GETTING NEXTPOSITION";
	return sf::FloatRect(-1.f, -1.f, -1.f, -1.f);
	
}

//functions
void Entity::setPosition(float x, float y)
{
	if (this->hitBoxComponent)
		this->hitBoxComponent->setPosition(sf::Vector2f(x, y));
	else
		this->sprite.setPosition(x, y);

}

void Entity::setNextPosition(float x, float y)
{
	if (this->hitBoxComponent)
		this->hitBoxComponent->setNextPosition(sf::Vector2f(x, y));
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


