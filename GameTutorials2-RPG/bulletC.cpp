#include "stdafx.h"
#include "bulletC.h"
#include "Entity.h"
#include "AnimationC.h"
#include "Movement.h"
#include "Hitbox.h"
#include "Attribute.h"
#include "physicsComponent.h"
#include "PhysicsDevice.h"

bulletC::bulletC(float x, float y, float velX, float velY, sf::Texture& texture, facing direction, Entity& owner)
	: running(true), xVel(velX), yVel(velY), Component("bullet", owner), death(false)
{
	float setVel = 2.f;
	sf::Vector2f multiplier(0.f,0.f);
	sf::Sprite& sprite = owner.getSprite(); 
	if (xVel != 0 || yVel != 0)
	{
		multiplier.x = velX/8;
		multiplier.y = velY/8;
	}
	

		switch (direction)
		{
		case(facing::DOWN):
			multiplier.y += setVel;
			multiplier.x += xVel / 4;
			startPosition.x = x + 10;
			startPosition.y = y + 32;
			break;
		case(facing::UP):
			multiplier.y += -setVel;
			multiplier.x += xVel / 4;
			startPosition.x = x - 10;
			startPosition.y = y - 32;
			break;
		case(facing::RIGHT):
			multiplier.x += setVel;
			multiplier.y += yVel / 4;;
			startPosition.x = x + 32;
			startPosition.y = y;
			break;
		case(facing::LEFT):
			multiplier.x += -setVel;
			multiplier.y += yVel / 4;;
			startPosition.x = x - 32;
			startPosition.y = y - 5;
			break;
		default:
			multiplier.y = setVel;
			multiplier.x = setVel;
			break;
		}
	
	xVel = multiplier.x;
	yVel = multiplier.y;

	sprite.setPosition(startPosition.x, startPosition.y);
	sprite.setTexture(texture);
	sprite.setTextureRect(sf::IntRect(0, 0, 32, 32));
}

void bulletC::updateAnimation(const float& dt)
{
	if (owner.getComponent<AnimationC>()->play("ATTACK", dt, false)) {
			death = true;
	};
}

void bulletC::update(const float& dt, const sf::Vector2f mousePosView)
{
	if (!death) {
		owner.getComponent<Movement>()->move(xVel, yVel, dt, true);
		updateAnimation(dt);
	}else
	{
		owner.getComponent<physicsComponent>()->pDevice->findBody(owner)->SetAwake(false);
		if (owner.getComponent<AnimationC>()->play("DEATH", dt, false))
			running = false;
		
	}
}

const bool bulletC::getRunning() const
{
	return running;
}

void bulletC::setRunning(const bool running)
{
	this->running = running;
}

void bulletC::setDeath(const bool death)
{
	this->death = death;
}

const sf::Vector2f bulletC::getStartPosition()
{
	return startPosition;
}
