#include "stdafx.h"
#include "HitboxComponent.h"

HitboxComponent::HitboxComponent(sf::Sprite& sprite, float offset_x, float offset_y, float width, float height)
	: sprite(sprite), offSetX(offset_x), offSetY(offset_y)
{
	this->hitbox.setPosition(this->sprite.getPosition().x + offSetX, this->sprite.getPosition().y + offSetY);
	this->hitbox.setSize(sf::Vector2f(width,height));
	this->hitbox.setFillColor(sf::Color::Transparent);
	this->hitbox.setOutlineThickness(1.f);
	this->hitbox.setOutlineColor(sf::Color::Red);
}

HitboxComponent::~HitboxComponent()
{
}

bool HitboxComponent::checkCollision(const sf::FloatRect& frect)
{
	return this->hitbox.getGlobalBounds().intersects(frect);
}

void HitboxComponent::update()
{
	this->hitbox.setPosition(this->sprite.getPosition().x + offSetX, this->sprite.getPosition().y + offSetY);
}

void HitboxComponent::render(sf::RenderTarget& target)
{
	target.draw(this->hitbox);
}
