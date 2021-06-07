#include "stdafx.h"
#include "Tile.h"

Tile::Tile(float x, float y, float gridSizeF, const sf::Texture& texture, const sf::IntRect& texture_rect)
{
	this->shape.setSize(sf::Vector2f(gridSizeF, gridSizeF));
	//this->shape.setFillColor(sf::Color::Green);
	this->shape.setPosition(x, y);
	//this->shape.setOutlineThickness(1.f);
	//this->shape.setOutlineColor(sf::Color::White);
	this->shape.setTexture(&texture);
	this->shape.setTextureRect(texture_rect);
}

void Tile::update()
{
}

void Tile::render(sf::RenderTarget& target)
{
	target.draw(shape);
}

std::ofstream& operator<<(std::ofstream& os, Tile& tile)
{
		os << tile.shape.getSize().x << tile.shape.getSize().y;
		os << tile.shape.getPosition().x << tile.shape.getPosition().y << " ";
	return os;
}
