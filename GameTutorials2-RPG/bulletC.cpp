#include "stdafx.h"
#include "bulletC.h"
#include "Entity.h"
#include "AnimationC.h"
#include "Movement.h"
#include "Hitbox.h"
#include "Attribute.h"
#include "physicsComponent.h"
#include "PhysicsDevice.h"

bulletC::bulletC(float x, float y, float velX, float velY, sf::Texture& texture, const unsigned short state, Entity& owner)
	: running(true), xVel(velX), yVel(velY), Component("bullet", owner)
{

	sf::Sprite& sprite = owner.getSprite(); 
	if (xVel == 0 && yVel == 0)
	{

		switch (state)
		{
		case(DOWNIDLE):
			yVel = 150.f; xVel = 30.f;
			sprite.setPosition(x + 10, y + 32);
			break;
		case(UPIDLE):
			yVel = -150.f;; xVel = -30.f;
			sprite.setPosition(x - 10, y - 32);
			break;
		case(RIGHTIDLE):
			xVel = 150.f;
			sprite.setPosition(x + 32, y);
			break;
		case(LEFTIDLE):
			xVel = -150.f;
			sprite.setPosition(x - 32, y - 5);
			break;
		default:
			xVel = 150.f;
			yVel = 150.f;
			break;
		}
		sprite.setPosition(x + (xVel * 32), y + (yVel * 32));
	}
	else {

		//Add bullet Direction Bounds when add switchstatments
		switch (state)
		{
		case(MOVING_RIGHT):
		case(RIGHTIDLE):
			if (xVel < 15.f)
				xVel = 15.f;
			sprite.setPosition(x + 32, y);
			break;
		case(MOVING_LEFT):
		case(LEFTIDLE):
			if (xVel > -15.f)
				xVel = -15.f;
			sprite.setPosition(x - 30, y);
			break;
		case(MOVING_UP):
		case(UPIDLE):
			if (yVel > -15.f)
				yVel = -15.f;
			sprite.setPosition(x - 10, y - 32);
			break;
		case(MOVING_DOWN):
		case(DOWNIDLE):
			if (yVel < 15.f)
				yVel = 15.f;
			sprite.setPosition(x + 10, y + 32);
			break;
		default:
			break;
		}

	}

	sprite.setTexture(texture);
	sprite.setTextureRect(sf::IntRect(0, 0, 32, 32));
}

void bulletC::updateAnimation(const float& dt)
{
	if (owner.getComponent<AnimationC>()->play("ATTACK", dt, false)) {
		running = false;
	};
}

void bulletC::initialize(std::shared_ptr<PhysicsDevice> p_device)
{
	owner.getComponent<physicsComponent>()->initialize(p_device);
}

void bulletC::update(const float& dt, const sf::Vector2f mousePosView)
{
	owner.getComponent<Movement>()->move(xVel, yVel, dt);
	updateAnimation(dt);
}

const bool bulletC::getRunning() const
{
	return running;
}
