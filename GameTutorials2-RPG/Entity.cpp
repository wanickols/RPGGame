#include "stdafx.h"
#include "Entity.h"
#include "Hitbox.h"
#include "Movement.h"
#include "AnimationC.h"
#include "Attribute.h"
#include "UserInput.h"
#include "Skills.h"
#include "Component.h"



void Entity::initVariables()
{
	

	componentList["hitbox"] = false;
	componentList["movement"] = false;
	componentList["animation"] = false;
	componentList["attribute"] = false;
	componentList["input"] = false;
	componentList["AI"] = false;
	componentList["skill"] = false;
	componentList["enemyData"] = false;
	componentList["Combat"] = false;
	componentList["item"] = false;
	componentList["enemyGui"] = false;
	componentList["physics"] = false;
	componentList["bullet"] = false;

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

//Accessors
const sf::Vector2f& Entity::getPosition()
{
	if (getComponent<Hitbox>())
		return getComponent<Hitbox>()->getPosition();

	return sprite.getPosition();
}

const float Entity::getDistance(Entity& entity)
{
	
	return sqrtf((float)pow((this->getCenterPosition().x - entity.getCenterPosition().x), 2) + (float)pow((this->getCenterPosition().y - entity.getCenterPosition().y), 2));
}

const float Entity::getDistance(const sf::Vector2f& position)
{
	return sqrtf((float)pow((this->getCenterPosition().x -position.x), 2) + (float)pow((this->getCenterPosition().y - position.y), 2));
}

const sf::Vector2f Entity::getCenterPosition()
{
	if (getComponent<Hitbox>())
		return getComponent<Hitbox>()->getPosition() +
		sf::Vector2f
		(
			getComponent<Hitbox>()->getGlobalBounds().width/2.f,
			getComponent<Hitbox>()->getGlobalBounds().height/2.f
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
	if (getComponent<Hitbox>()) {
		gridPosition.x = (int)getComponent<Hitbox>()->getPosition().x;
		gridPosition.y = (int)getComponent<Hitbox>()->getPosition().y;

		gridPosition.x = gridPosition.x / gridSizeI;
		gridPosition.y = gridPosition.y / gridSizeI;

		return gridPosition;
	}


	return sf::Vector2i(
		(int)sprite.getPosition().x / gridSizeI,
		(int)sprite.getPosition().y / gridSizeI
	);
}

const sf::FloatRect& Entity::getNextPositionBounds(const float& dt)
{
	
	return getComponent<Hitbox>()->getNextPosition(getComponent<Movement>()->getVelocity() * dt);
	
}

void Entity::addComponent(std::shared_ptr<Component> component)
{
		componentList.find(component->getName())->second = true;
		components.push_back(component);
}

//functions
void Entity::setPosition(float x, float y)
{
	if (getComponent<Hitbox>())
		getComponent<Hitbox>()->setPosition(sf::Vector2f(x, y));
	else
		sprite.setPosition(x, y);

}

void Entity::setNextPosition(float x, float y)
{
	if (getComponent<Hitbox>())
		getComponent<Hitbox>()->setNextPosition(sf::Vector2f(x, y));
	else
		sprite.setPosition(x, y);
}

void Entity::move(const float dir_x, const float dir_y, const float& dt, bool player)
{
	getComponent<Movement>()->move(dir_x, dir_y, dt, player); //setsVelocity

	//if (Skills)
//	{	
	//	Skills->addExp("Endurance", 1);
	//}
}

const sf::FloatRect Entity::getGlobalBounds()
{
	if (getComponent<Hitbox>())
		return getComponent<Hitbox>()->getGlobalBounds();

	return sprite.getGlobalBounds();
}

void Entity::stopVelocity()
{
	if (getComponent<Movement>())
		getComponent<Movement>()->stopVelocity();
}

void Entity::stopVelocityX()
{
	if (getComponent<Movement>())
		getComponent<Movement>()->stopVelocityX();
}

void Entity::stopVelocityY()
{
	if (getComponent<Movement>())
		getComponent<Movement>()->stopVelocityY();
}

void Entity::update(const float& dt, const sf::Vector2f mousePosView)
{
	for(auto& i : components)
	{
		i->update(dt, mousePosView);
	}
}

void Entity::render(sf::RenderTarget& target, sf::Shader* shader, sf::Vector2f light_position, const bool show_hitbox)
{
	for (auto& i : components)
	{
		i->render(target, shader, light_position, show_hitbox);
	}
}

sf::Sprite& Entity::getSprite()
{
	return sprite;
}


