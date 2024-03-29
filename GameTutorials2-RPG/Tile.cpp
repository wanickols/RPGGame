#include "stdafx.h"
#include "Tile.h"
#include "Graph.h"
#include "physicsComponent.h"
#include "PhysicsDevice.h"
#include "AnimationC.h"
#include "Constants.h"

Tile::Tile(float x, float y, sf::Texture& texture, const sf::IntRect& texture_rect, std::shared_ptr<Graph> graph, std::shared_ptr<PhysicsDevice> p_device, bool collision, short type)
	: collision(collision), type(type)
{
	
	
	
	//shape.setFillColor(sf::Color::Green);
	shape.setPosition(x, y);
	//shape.setOutlineThickness(1.f);
	//shape.setOutlineColor(sf::Color::White);
	shape.setTexture(texture);
	shape.setTextureRect(texture_rect);

	node = std::make_shared<graphNode>(graph->getNode(sf::Vector2i((int)x / 64, (int)y / 64)));
	if (collision) {
		std::shared_ptr<AnimationC> anim = std::make_shared<AnimationC>(sprite, texture, x, y, *this);
		addComponent(anim);
		
		GAME_PHYSICS physics(GAME_BODY_TYPE::GAME_STATIC, GAME_OBJECT_SHAPE::GAME_RECTANGLE, texture_rect.width, texture_rect.height, 1000.f, 0.f, 0.f, 1000.f, 1000.f, 1000.f, 0.f, 0.f, CATEGORY_WALL, MASK_WALL);
		physics.offSetX = 20.f;
		std::shared_ptr<physicsComponent> physC = std::make_shared<physicsComponent>(physics, p_device, *this);
		addComponent(physC);
		node->isObstacle = true;
	}

	

	
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
	Entity::update(dt, sf::Vector2f());
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
