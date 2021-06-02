#include "stdafx.h"
#include "Tile.h"

Tile::Tile(float x, float y, float gridSizeF)
{
	this->shape.setSize(sf::Vector2f(gridSizeF, gridSizeF));
	this->shape.setFillColor(sf::Color::Green);
	this->shape.setPosition(x, y);
	this->shape.setOutlineThickness(1.f);
	this->shape.setOutlineColor(sf::Color::White);
}

void Tile::update()
{
}

void Tile::render(sf::RenderTarget& target)
{
	target.draw(shape);
}
