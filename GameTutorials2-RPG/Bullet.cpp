#include "stdafx.h"
#include "Bullet.h"


Bullet::Bullet(float x, float y, float velX, float velY, sf::Texture& texture, const unsigned short state)
	: running(true), xVel(velX), yVel(velY)
{

	if (xVel == 0 && yVel == 0)
	{

		switch (state)
		{
		case(DOWNIDLE): 
			yVel = 2.f; xVel = .3f;
			setPosition(x + 10, y + 32);
			break; 
		case(UPIDLE):
			yVel = -2.f; xVel = -.3f;
			setPosition(x - 10, y - 32);
			break;
		case(RIGHTIDLE):
			xVel = 2.f;
			setPosition(x + 32, y);
			break;
		case(LEFTIDLE):
			xVel = -2.f;
			setPosition(x - 32, y-5);
			break;
		default:
			xVel = 2.f;
			yVel = 2.f;
			break;
		}
		setPosition(x + (xVel * 32), y + (yVel * 32));
	}
	else {
		//FIXME SWITCH STAMENNT
		//Add bullet Direction Bounds when add switchstatments
		switch (state) 
		{
		case(MOVING_RIGHT):
		case(RIGHTIDLE):
			if (xVel < 1.5f)
				xVel = 1.5f;
			setPosition(x + 32, y);
			break;
		case(MOVING_LEFT):
		case(LEFTIDLE):
			if (xVel > -1.5f)
				xVel = -1.5f;
			setPosition(x - 30, y+10);
			break;
		case(MOVING_UP):
		case(UPIDLE):
			if (yVel > -1.5f)
				yVel = -1.5f;
			setPosition(x - 10, y - 32);
			break;
		case(MOVING_DOWN):
		case(DOWNIDLE):
			if (yVel < 1.5f)
				yVel = 1.5f;
			setPosition(x + 10, y + 32);
			break;
		default:
			break;
		}

	}

	sprite.setTexture(texture);
	sprite.setTextureRect(sf::IntRect(0,0,32,32));
	createAnimationComponent(texture);
	createMovementComponent(700.f, 1300.f, 400.f);
	createHitBoxComponent(sprite, 6.f, 2.f, 27, 27);
	animationComponent->addAnimation("ATTACK", 20.f, 0, 0, 7, 0, 32, 32);
}

void Bullet::updateAnimation(const float& dt)
{
	if (animationComponent->play("ATTACK", dt, false)) {
		running = false;
	};
}

void Bullet::update(const float& dt, const sf::Vector2f& mousePosView)
{
	movementComponent->move(xVel, yVel, dt);
	
	
	movementComponent->update(dt);
	updateAnimation(dt);
	hitBoxComponent->update();
}

void Bullet::render(sf::RenderTarget& target, sf::Shader* shader, sf::Vector2f light_position, const bool show_hitbox)
{
	if (shader) {
		shader->setUniform("hasTexture", true);
		shader->setUniform("lightPos", light_position);

		target.draw(sprite, shader);
	}
	else {
		target.draw(sprite);
	}
}

const bool Bullet::getRunning() const
{
	return running;
}
