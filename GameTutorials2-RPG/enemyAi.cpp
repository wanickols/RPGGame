#include "stdafx.h"
#include "enemyAi.h"
#include "Movement.h"
#include "AnimationC.h"
#include "Entity.h"

enemyAi::enemyAi(Entity* owner)
	: Component("AI", owner)
{
}

void enemyAi::update(const float& dt, const sf::Vector2f mousePosView)
{
	owner->getComponent<Movement>()->setDirection(facing::RIGHT);
	if (owner->getComponent<Movement>()->getDirection() == facing::RIGHT)
	{	
		owner->getComponent<AnimationC>()->play("WALKRIGHT", dt, false);
	}

}

void enemyAi::render(sf::RenderTarget& target, sf::Shader* shader, sf::Vector2f light_position, const bool show_hitbox)
{
}
