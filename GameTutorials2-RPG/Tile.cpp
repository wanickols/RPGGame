#include "stdafx.h"
#include "Tile.h"

Tile::Tile(float x, float y, const sf::Texture& texture, const sf::IntRect& texture_rect, bool collision, short type)
	: collision(collision), type(type)
{
	
	//shape.setFillColor(sf::Color::Green);
	shape.setPosition(x, y);
	//shape.setOutlineThickness(1.f);
	//shape.setOutlineColor(sf::Color::White);
	shape.setTexture(texture);
	shape.setTextureRect(texture_rect);
}

//Accessors
const short& Tile::getType() const
{
	return type;
}

const bool Tile::getCollision() const
{
	return collision;
}

const sf::Vector2f& Tile::getPosition() const
{
	return shape.getPosition();
}

const sf::FloatRect Tile::getGlobalBounds() const
{
	return shape.getGlobalBounds();
}

std::ofstream& Tile::getStringTile(std::ofstream& os)
{
	os << type << " " << shape.getTextureRect().left << " " << shape.getTextureRect().top
		<< " " << collision;
	return os;
}

const bool Tile::intersects(const sf::FloatRect bounds) const
{
	return shape.getGlobalBounds().intersects(bounds);
}

//Functions
void Tile::update(const float& dt)
{
}

void Tile::render(sf::RenderTarget& target, const sf::Vector2f playerPosition, sf::Shader* shader)
{
	if (shader) {
		shader->setUniform("hasTexture", true);
		shader->setUniform("lightPos", playerPosition);

		target.draw(shape, shader);
	}
	else
		target.draw(shape);
}

std::ofstream& operator<<(std::ofstream& os, Tile& tile)
{
	//Texture rect x y, type, collision
	os << tile.type << " " << tile.shape.getTextureRect().left << " " << tile.shape.getTextureRect().top
		<< " " << tile.collision;
	return os;
}
