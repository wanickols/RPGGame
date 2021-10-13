#include "stdafx.h"
#include "Entity.h"

void Entity::initVariables()
{
	hitBoxComponent = NULL;
	movementComponent = NULL;
	attributeComponent = NULL;
	

	componentList["hitbox"] = false;
	componentList["movement"] = false;
	componentList["animation"] = false;
	componentList["attribute"] = false;
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

void Entity::createMovementComponent(const float maxVelocity, const float acceleration, const float deceleration)
{
	movementComponent = std::make_unique<MovementComponent>(sprite, maxVelocity, acceleration, deceleration);
}

void Entity::creatAttributeComponent(int level)
{
	attributeComponent = std::make_shared<AttributeComponent>(level);
}

void Entity::createSkillComponent()
{
	skillComponent = std::make_unique<SkillComponent>();
}

void Entity::createHitBoxComponent(sf::Sprite& sprite, const float offset_x, const float offset_y, float width, float height)
{
	hitBoxComponent = std::make_unique<HitboxComponent>(sprite, offset_x, offset_y, width, height);
}

//Accessors
const sf::Vector2f& Entity::getPosition() const
{
	if (hitBoxComponent)
		return hitBoxComponent->getPosition();

	return sprite.getPosition();
}

const sf::Vector2f Entity::getCenterPosition() const
{
	if (hitBoxComponent)
		return hitBoxComponent->getPosition() +
		sf::Vector2f
		(
			hitBoxComponent->getGlobalBounds().width/2.f,
			hitBoxComponent->getGlobalBounds().height/2.f
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
	if (hitBoxComponent) {
		gridPosition.x = (int)hitBoxComponent->getPosition().x;
		gridPosition.y = (int)hitBoxComponent->getPosition().y;

		gridPosition.x = gridPosition.x / gridSizeI;
		gridPosition.y = gridPosition.y / gridSizeI;

		return gridPosition;
	}


	return sf::Vector2i(
		(int)sprite.getPosition().x / gridSizeI,
		(int)sprite.getPosition().y / gridSizeI
	);
}

const sf::FloatRect& Entity::getNextPositionBounds(const float& dt) const
{
	
	return hitBoxComponent->getNextPosition(movementComponent->getVelocity() * dt);
	
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
	if (hitBoxComponent)
		hitBoxComponent->setPosition(sf::Vector2f(x, y));
	else
		sprite.setPosition(x, y);

}

void Entity::setNextPosition(float x, float y)
{
	if (hitBoxComponent)
		hitBoxComponent->setNextPosition(sf::Vector2f(x, y));
	else
		sprite.setPosition(x, y);
}

void Entity::move(const float dir_x, const float dir_y, const float& dt, bool player)
{
	movementComponent->move(dir_x, dir_y, dt, player); //setsVelocity

	if (skillComponent)
	{	
		skillComponent->addExp("Endurance", 1);
	}
}

const sf::FloatRect Entity::getGlobalBounds() const
{
	if (hitBoxComponent)
		return hitBoxComponent->getGlobalBounds();

	return sprite.getGlobalBounds();
}

void Entity::stopVelocity()
{
	if (movementComponent)
		movementComponent->stopVelocity();
}

void Entity::stopVelocityX()
{
	if (movementComponent)
		movementComponent->stopVelocityX();
}

void Entity::stopVelocityY()
{
	if (movementComponent)
		movementComponent->stopVelocityY();
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


