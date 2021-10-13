#include "stdafx.h"
#include "Entity.h"
#include "HitboxComponent.h"
#include "MovementComponent.h"
#include "AnimationComponent.h"
#include "AttributeComponent.h"
#include "InputComponent.h"
#include "SkillComponent.h"
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
	if (getComponent<HitboxComponent>())
		return getComponent<HitboxComponent>()->getPosition();

	return sprite.getPosition();
}

const sf::Vector2f Entity::getCenterPosition()
{
	if (getComponent<HitboxComponent>())
		return getComponent<HitboxComponent>()->getPosition() +
		sf::Vector2f
		(
			getComponent<HitboxComponent>()->getGlobalBounds().width/2.f,
			getComponent<HitboxComponent>()->getGlobalBounds().height/2.f
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
	if (getComponent<HitboxComponent>()) {
		gridPosition.x = (int)getComponent<HitboxComponent>()->getPosition().x;
		gridPosition.y = (int)getComponent<HitboxComponent>()->getPosition().y;

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
	
	return getComponent<HitboxComponent>()->getNextPosition(getComponent<MovementComponent>()->getVelocity() * dt);
	
}

void Entity::addComponent(std::shared_ptr<Component> component)
{
	if (!componentList.find(component->getName())->second) //checks if component exist already
	{
		componentList.find(component->getName())->second = true;
		components.push_back(component);
	}
	else
		std::cout << "COMPONENT already exist" << std::endl;
}

//functions
void Entity::setPosition(float x, float y)
{
	if (getComponent<HitboxComponent>())
		getComponent<HitboxComponent>()->setPosition(sf::Vector2f(x, y));
	else
		sprite.setPosition(x, y);

}

void Entity::setNextPosition(float x, float y)
{
	if (getComponent<HitboxComponent>())
		getComponent<HitboxComponent>()->setNextPosition(sf::Vector2f(x, y));
	else
		sprite.setPosition(x, y);
}

void Entity::move(const float dir_x, const float dir_y, const float& dt, bool player)
{
	getComponent<MovementComponent>()->move(dir_x, dir_y, dt, player); //setsVelocity

	//if (skillComponent)
//	{	
	//	skillComponent->addExp("Endurance", 1);
	//}
}

const sf::FloatRect Entity::getGlobalBounds()
{
	if (getComponent<HitboxComponent>())
		return getComponent<HitboxComponent>()->getGlobalBounds();

	return sprite.getGlobalBounds();
}

void Entity::stopVelocity()
{
	if (getComponent<MovementComponent>())
		getComponent<MovementComponent>()->stopVelocity();
}

void Entity::stopVelocityX()
{
	if (getComponent<MovementComponent>())
		getComponent<MovementComponent>()->stopVelocityX();
}

void Entity::stopVelocityY()
{
	if (getComponent<MovementComponent>())
		getComponent<MovementComponent>()->stopVelocityY();
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


