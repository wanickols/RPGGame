#include "stdafx.h"
#include "Tile.h"

Tile::Tile(float x, float y, float gridSizeF, const sf::Texture& texture, const sf::IntRect& texture_rect, bool collision, short type)
	: collision(collision), type(type)
{
	this->shape.setSize(sf::Vector2f(gridSizeF, gridSizeF));
	//this->shape.setFillColor(sf::Color::Green);
	this->shape.setPosition(x, y);
	//this->shape.setOutlineThickness(1.f);
	//this->shape.setOutlineColor(sf::Color::White);
	this->shape.setTexture(&texture);
	this->shape.setTextureRect(texture_rect);
}

//Accessors
const sf::Vector2f& Tile::getPosition() const
{
	return this->shape.getPosition();
}

//Functions
void Tile::update()
{
}

void Tile::render(sf::RenderTarget& target)
{
	target.draw(shape);
}

std::ofstream& operator<<(std::ofstream& os, Tile& tile)
{
	//Texture rect x y, type, collision
	os << tile.shape.getTextureRect().left << " " << tile.shape.getTextureRect().top
		<< " " << tile.collision << " " << tile.type;
	return os;
}
