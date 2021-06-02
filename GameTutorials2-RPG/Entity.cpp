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

//functions
void Entity::setPosition(float x, float y)
{
	
		this->sprite.setPosition(x, y);

}

void Entity::move(const float dir_x, const float dir_y, const float& dt)
{
	if (this->movementComponent) {
		this->movementComponent->move(dir_x, dir_y, dt); //setsVelocity
	}
}

void Entity::update(const float& dt)
{
	//if (this->movementComponent)
		//movementComponent->update(dt);
}

void Entity::render(sf::RenderTarget& target)
{
	target.draw(this->sprite);
	if (this->hitBoxComponent) {
		this->hitBoxComponent->render(target);
	}
}
