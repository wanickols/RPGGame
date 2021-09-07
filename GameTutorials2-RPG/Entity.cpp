#include "stdafx.h"
#include "Entity.h"

void Entity::initVariables()
{
	hitBoxComponent = NULL;
	movementComponent = NULL;
	animationComponent = NULL;
	attributeComponent = NULL;
	
}

Entity::Entity()
{

	initVariables();
}

Entity::~Entity()
{
}

//Component functions
void Entity::setTexture(sf::Texture& texture)
{
	//texture = std::make_unique<sf::Texture>(&texture);
	sprite.setTexture(texture);
}

void Entity::createMovementComponent(const float maxVelocity, const float acceleration, const float deceleration)
{
	movementComponent = std::make_unique<MovementComponent>(sprite, maxVelocity, acceleration, deceleration);
}

void Entity::createAnimationComponent(sf::Texture& texture_sheet)
{
	animationComponent = std::make_unique<AnimationComponent>(sprite, texture_sheet);
}

void Entity::creatAttributeComponent(int level)
{
	attributeComponent = std::make_shared<AttributeComponent>(level);
}

void Entity::createHitBoxComponent(sf::Sprite& sprite, const float offset_x, const float offset_y, float width, float height)
{
	hitBoxComponent = std::make_unique<HitboxComponent>(sprite, offset_x, offset_y, width, height);
}

//Accessors
const sf::Vector2f& Entity::getPosition() const
{
	if (hitBoxComponent)
		return hitBoxComponent->getPosition();

	return sprite.getPosition();
}

const sf::Vector2f Entity::getCenterPosition() const
{
	if (hitBoxComponent)
		return hitBoxComponent->getPosition() +
		sf::Vector2f
		(
			hitBoxComponent->getGlobalBounds().width/2.f,
			hitBoxComponent->getGlobalBounds().height/2.f
		);

	return sprite.getPosition() + 
		sf::Vector2f
	(
		sprite.getGlobalBounds().width / 2.f,
		sprite.getGlobalBounds().height / 2.f
	);;
}

const sf::Vector2i Entity::getGridPosition(const int& gridSizeI)
{
	if (hitBoxComponent) {
		gridPosition.x = (int)hitBoxComponent->getPosition().x;
		gridPosition.y = (int)hitBoxComponent->getPosition().y;

		gridPosition.x = gridPosition.x / gridSizeI;
		gridPosition.y = gridPosition.y / gridSizeI;

		return gridPosition;
	}


	return sf::Vector2i(
		(int)sprite.getPosition().x / gridSizeI,
		(int)sprite.getPosition().y / gridSizeI
	);
}

const sf::FloatRect& Entity::getNextPositionBounds(const float& dt) const
{
	
	return hitBoxComponent->getNextPosition(movementComponent->getVelocity() * dt);
	
}

//functions
void Entity::setPosition(float x, float y)
{
	if (hitBoxComponent)
		hitBoxComponent->setPosition(sf::Vector2f(x, y));
	else
		sprite.setPosition(x, y);

}

void Entity::setNextPosition(float x, float y)
{
	if (hitBoxComponent)
		hitBoxComponent->setNextPosition(sf::Vector2f(x, y));
	else
		sprite.setPosition(x, y);
}

void Entity::move(const float dir_x, const float dir_y, const float& dt)
{
	if (movementComponent) {
		movementComponent->move(dir_x, dir_y, dt); //setsVelocity
	}
}

const sf::FloatRect Entity::getGlobalBounds() const
{
	if (hitBoxComponent)
		return hitBoxComponent->getGlobalBounds();

	return sprite.getGlobalBounds();
}

void Entity::stopVelocity()
{
	if (movementComponent)
		movementComponent->stopVelocity();
}

void Entity::stopVelocityX()
{
	if (movementComponent)
		movementComponent->stopVelocityX();
}

void Entity::stopVelocityY()
{
	if (movementComponent)
		movementComponent->stopVelocityY();
}


