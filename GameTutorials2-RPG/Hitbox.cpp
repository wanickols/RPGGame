#include "stdafx.h"
#include "Hitbox.h"
#include "Entity.h"

Hitbox::Hitbox(sf::Sprite& sprite, float offset_x, float offset_y, float width, float height, Entity* owner)
	: sprite(sprite), offSetX(offset_x), offSetY(offset_y), Component("hitbox", owner)
{
	nextPosition.left = 0.f;
	nextPosition.top = 0.f;
	nextPosition.width = width;
	nextPosition.height = height;

	hitbox.setPosition(sprite.getPosition().x +  offSetX, sprite.getPosition().y + offSetY + height/2);
	hitbox.setSize(sf::Vector2f(width, height));
	hitbox.setFillColor(sf::Color::Transparent);
	hitbox.setOutlineThickness(-1.f);
	hitbox.setOutlineColor(sf::Color::Red);
}

Hitbox::~Hitbox()
{
}

const sf::Vector2f& Hitbox::getPosition() const
{
	return hitbox.getPosition();
}

const sf::FloatRect& Hitbox::getNextPosition(const sf::Vector2f& velocity)
{
	nextPosition.left = hitbox.getPosition().x + velocity.x;
	nextPosition.top = hitbox.getPosition().y + velocity.y;
	return nextPosition;
}

void Hitbox::setPosition(const sf::Vector2f& position)
{
	hitbox.setPosition(position);
	sprite.setPosition(position.x - offSetX, position.y - offSetY - sprite.getTextureRect().height / 4);
}

void Hitbox::setNextPosition(const sf::Vector2f& position)
{
	nextPosition.left = position.x;
	nextPosition.top = position.y;
}

bool Hitbox::intersect(const sf::FloatRect& frect)
{
	return hitbox.getGlobalBounds().intersects(frect);
}

void Hitbox::render(sf::RenderTarget& target, sf::Shader* shader, sf::Vector2f light_position, const bool show_hitbox)
{
	target.draw(hitbox);
}

const sf::FloatRect Hitbox::getGlobalBounds() const
{
	return hitbox.getGlobalBounds();
}

void Hitbox::update(const float& dt, const sf::Vector2f mousePosView)
{
	hitbox.setPosition(sprite.getPosition().x + offSetX, sprite.getPosition().y + offSetY + sprite.getTextureRect().height/4);
}