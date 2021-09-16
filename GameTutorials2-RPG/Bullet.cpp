#include "stdafx.h"
#include "Bullet.h"


Bullet::Bullet(float x, float y, float velX, float velY, sf::Texture& texture)
	: running(true), xVel(velX), yVel(velY)
{
	
	if (xVel == 0 && yVel == 0)
		yVel = 1;
	this->setPosition(x, y);
	sprite.setTexture(texture);
	sprite.setTextureRect(sf::IntRect(0,0,64,64));
	createAnimationComponent(texture);
	createMovementComponent(700.f, 1300.f, 400.f);
	createHitBoxComponent(sprite, 6.f, 2.f, 21, 30);
	animationComponent->addAnimation("ATTACK", 15.f, 0, 0, 8, 0, 64, 64);
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
