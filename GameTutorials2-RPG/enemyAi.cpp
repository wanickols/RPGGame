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
	
	if (owner->getComponent<Movement>()->getDirection() == facing::RIGHT)
	{	
		owner->getComponent<AnimationC>()->play("WALKRIGHT", dt, false);
		owner->move(1.f, 0.f, dt);
	}
	else if (owner->getComponent<Movement>()->getDirection() == facing::LEFT)
	{
		owner->getComponent<AnimationC>()->play("WALKLEFT", dt, false);
		owner->move(-1.f, 0.f, dt);
	}
	else if (owner->getComponent<Movement>()->getDirection() == facing::UP)
	{
		owner->getComponent<AnimationC>()->play("WALKUP", dt, false);
		owner->move(0.f, -1.f, dt);
	}
	else if (owner->getComponent<Movement>()->getDirection() == facing::DOWN)
	{
		owner->getComponent<AnimationC>()->play("WALKDOWN", dt, false);
		owner->move(0.f, 1.f, dt);
	}
	else 
		owner->getComponent<AnimationC>()->play("DOWNIDLE", dt, false);
}

void enemyAi::render(sf::RenderTarget& target, sf::Shader* shader, sf::Vector2f light_position, const bool show_hitbox)
{
}

void enemyAi::reactions(std::shared_ptr<Entity> player)
{
	if (abs(player->getPosition().x - owner->getPosition().x) > abs(player->getPosition().y - owner->getPosition().y)) {
		if (player->getPosition().x > owner->getPosition().x)
			owner->getComponent<Movement>()->setDirection(facing::RIGHT);
		else if (player->getPosition().x < owner->getPosition().x)
			owner->getComponent<Movement>()->setDirection(facing::LEFT);
	}
	else
	{
		if (player->getPosition().y > owner->getPosition().y)
			owner->getComponent<Movement>()->setDirection(facing::DOWN);
		else if (player->getPosition().y < owner->getPosition().y)
			owner->getComponent<Movement>()->setDirection(facing::UP);
	}

}

void enemyAi::setIdle()
{
	owner->getComponent<Movement>()->setDirection(facing::IDLE);
}
