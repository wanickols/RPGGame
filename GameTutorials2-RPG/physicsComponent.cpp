#include "stdafx.h"
#include "physicsComponent.h"
#include "PhysicsDevice.h"
#include "Entity.h"
#include "ComponentInclude.h"

physicsComponent::physicsComponent(GAME_PHYSICS physics, Entity& owner)
	: Component("physics", owner), physics(physics)
{
	offset.x = physics.offSetX;
	offset.y = physics.offSetY;
}

physicsComponent::~physicsComponent()
{
	pDevice->removeEntity(owner);
}

void physicsComponent::update(const float& dt, const sf::Vector2f mousePosView)
{
}

void physicsComponent::initialize(std::shared_ptr<PhysicsDevice> p_device)
{
	pDevice = p_device;
	pDevice->createFixture(owner, physics);
}

const sf::Vector2f physicsComponent::getOffset()
{
	return offset;
}

void physicsComponent::collisions(Entity* collider)
{
	//checks for combat
	if (owner.getComponent<EnemyData>() != nullptr) 
	{
		owner.getComponent<Attribute>()->isDead() == true;
	}
	if(owner.getComponent<UserInput>()!= nullptr)
	{
		std::cout << "Player colided with something that is moving" << "\n";
	}
}
