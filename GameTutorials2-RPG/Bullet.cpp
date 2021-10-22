#include "stdafx.h"
#include "Bullet.h"
#include "AnimationC.h"
#include "Movement.h"
#include "Hitbox.h"
#include "Attribute.h"

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
			setPosition(x - 30, y);
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
	
	//Hitbox
	std::shared_ptr<Hitbox> hitbox = std::make_shared<Hitbox>(sprite, 4.f, 2.f, 20.f, 20.f, this); //hitbox for player set here
	addComponent(hitbox);

	//Animation
	std::shared_ptr<AnimationC> animation = std::make_shared<AnimationC>(sprite, texture, getComponent<Hitbox>()->getPosition().x, getComponent<Hitbox>()->getPosition().y, this);
	addComponent(animation);
	getComponent<AnimationC>()->addAnimation("ATTACK", 20.f, 0, 0, 7, 0, 32, 32);

	//Movement
	std::shared_ptr<Movement> movement = std::make_shared<Movement>(sprite, 600.f, 1300.f, 400.f, this); //speed for bullet set here
	addComponent(movement);
	
	std::shared_ptr<Attribute> attribute = std::make_shared<Attribute>(1, this); //speed for bullet set here
	addComponent(attribute);
	attribute->range = 40;
	
}

void Bullet::updateAnimation(const float& dt)
{
	if (getComponent<AnimationC>()->play("ATTACK", dt, false)) {
		running = false;
	};
}

void Bullet::update(const float& dt, const sf::Vector2f mousePosView)
{
	Entity::update(dt, mousePosView);
	getComponent<Movement>()->move(xVel, yVel, dt);	
	updateAnimation(dt);
}

void Bullet::render(sf::RenderTarget& target, sf::Shader* shader, sf::Vector2f light_position, const bool show_hitbox)
{
	if (shader) {
		shader->setUniform("hasTexture", true);
		shader->setUniform("lightPos", this->getCenterPosition());

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
