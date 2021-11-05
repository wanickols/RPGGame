#include "stdafx.h"
#include "physicsComponent.h"

physicsComponent::physicsComponent(Entity& owner)
	: Component("physics", owner)
{
}

void physicsComponent::update(const float& dt, const sf::Vector2f mousePosView)
{
}
