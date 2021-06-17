#include "stdafx.h"
#include "HitboxComponent.h"

HitboxComponent::HitboxComponent(sf::Sprite& sprite, float offset_x, float offset_y, float width, float height)
	: sprite(sprite), offSetX(offset_x), offSetY(offset_y)
{
	this->nextPosition.left = 0.f;
	this->nextPosition.top = 0.f;
	this->nextPosition.width = width;
	this->nextPosition.height = height;
	
	this->hitbox.setPosition(this->sprite.getPosition().x + offSetX, this->sprite.getPosition().y + offSetY);
	this->hitbox.setSize(sf::Vector2f(width, height));
	this->hitbox.setFillColor(sf::Color::Transparent);
	this->hitbox.setOutlineThickness(-1.f);
	this->hitbox.setOutlineColor(sf::Color::Red);
}

HitboxComponent::~HitboxComponent()
{
}

const sf::Vector2f& HitboxComponent::getPosition() const
{
	return this->hitbox.getPosition();
}

const sf::FloatRect HitboxComponent::getNextPosition(const sf::Vector2f& velocity)
{
	
	nextPosition.left = this->hitbox.getPosition().x + velocity.x;
	nextPosition.top = this->hitbox.getPosition().y + velocity.y;
	
	return this->nextPosition;
}

void HitboxComponent::setPosition(const sf::Vector2f& position)
{

	this->hitbox.setPosition(position);
	this->sprite.setPosition(position.x - this->offSetX, position.y - this->offSetY);
}

bool HitboxComponent::intersect(const sf::FloatRect& frect)
{
	return this->hitbox.getGlobalBounds().intersects(frect);
}

const sf::FloatRect HitboxComponent::getGlobalBounds() const
{
	return this->hitbox.getGlobalBounds();
}

void HitboxComponent::update()
{
	this->hitbox.setPosition(this->sprite.getPosition().x + offSetX, this->sprite.getPosition().y + offSetY);
}

void HitboxComponent::render(sf::RenderTarget& target)
{
	target.draw(this->hitbox);
}
