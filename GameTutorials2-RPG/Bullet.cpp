#include "stdafx.h"
#include "Bullet.h"


Bullet::Bullet(float x, float y, float velX, float velY, sf::Texture& texture, const unsigned short state)
	: running(true), xVel(velX), yVel(velY)
{
	
	if (xVel == 0 && yVel == 0)
	{
		if (state == DOWNIDLE)
			yVel = 1.f;
		else if (state == UPIDLE)
			yVel = -1.f;
		else if (state == RIGHTIDLE)
			xVel = 1.f;
		else if (state == LEFTIDLE)
			xVel = -1.f;
		
	}
		
	this->setPosition(x, y);
	sprite.setTexture(texture);
	sprite.setTextureRect(sf::IntRect(0,0,32,32));
	createAnimationComponent(texture);
	createMovementComponent(700.f, 1300.f, 400.f);
	createHitBoxComponent(sprite, 6.f, 2.f, 21, 30);
	animationComponent->addAnimation("ATTACK", 20.f, 0, 0, 7, 0, 32, 32);
}

void Bullet::updateAnimation(const float& dt)
{
	if (animationComponent->play("ATTACK", dt, false)) {
		running = false;
	};
}

void Bullet::update(const float& dt)
{
	movementComponent->move(xVel, yVel, dt);
	
	
	movementComponent->update(dt);
	updateAnimation(dt);
}

void Bullet::render(sf::RenderTarget& target, sf::Shader* shader, const bool show_hitbox)
{
	target.draw(sprite);
}

const bool Bullet::getRunning() const
{
	return running;
}
