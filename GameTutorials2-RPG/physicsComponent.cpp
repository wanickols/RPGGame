#include "stdafx.h"
#include "physicsComponent.h"
#include "PhysicsDevice.h"
#include "Entity.h"
#include "ComponentInclude.h"

physicsComponent::physicsComponent(GAME_PHYSICS physics, std::shared_ptr<PhysicsDevice> p_device, Entity& owner)
	: Component("physics", owner), physics(physics)
{
	offset.x = physics.offSetX;
	offset.y = physics.offSetY;
	pDevice = p_device;
	if(pDevice!= nullptr)
		pDevice->createFixture(owner, physics);
}

physicsComponent::~physicsComponent()
{
	pDevice->removeEntity(owner);
}

void physicsComponent::update(const float& dt, const sf::Vector2f mousePosView)
{
}

const sf::Vector2f physicsComponent::getOffset()
{
	return offset;
}

void physicsComponent::staticCollisions(Entity* collider)
{
	if (owner.getComponent<bulletC>() != nullptr)
	{
		owner.getComponent<bulletC>()->setDeath(true);
	}
}

void physicsComponent::dynamicCollisions(Entity* collider)
{
	//checks for combat
	if (owner.getComponent<EnemyData>() != nullptr) 
	{
		if (collider->getComponent<Combat>() != nullptr && collider->getComponent<EnemyData>() == nullptr) {
			collider->getComponent<Combat>()->defend(owner);
		}
	}
	if(owner.getComponent<UserInput>()!= nullptr)
	{
		std::cout << "Player colided with something that is moving" << "\n";
	}
	if(owner.getComponent<bulletC>() != nullptr)
	{
		owner.getComponent<bulletC>()->setDeath(true);
	}
}
