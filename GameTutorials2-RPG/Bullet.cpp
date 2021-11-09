#include "stdafx.h"
#include "Bullet.h"
#include "AnimationC.h"
#include "Movement.h"
#include "Hitbox.h"
#include "Attribute.h"
#include "physicsComponent.h"
#include "PhysicsDevice.h"
#include "bulletC.h"


Bullet::Bullet(float x, float y, float velX, float velY, sf::Texture& texture, const unsigned short state)
{


	GAME_PHYSICS physics(GAME_BODY_TYPE::GAME_DYNAMIC, GAME_OBJECT_SHAPE::GAME_CIRCLE,31,31, .5f, 1.0f, .9f, .1f, .7f, 4.f, 0.f, 10.f);

	std::shared_ptr<physicsComponent> physicsC = std::make_shared<physicsComponent>(physics, *this); //itemComp for player set here

	addComponent(physicsC);


	//Hitbox
	std::shared_ptr<Hitbox> hitbox = std::make_shared<Hitbox>(sprite, 4.f, 2.f, 20.f, 20.f, *this); //hitbox for player set here
	addComponent(hitbox);

	//Animation
	std::shared_ptr<AnimationC> animation = std::make_shared<AnimationC>(sprite, texture, getComponent<Hitbox>()->getPosition().x, getComponent<Hitbox>()->getPosition().y, *this);
	addComponent(animation);
	getComponent<AnimationC>()->addAnimation("ATTACK", 20.f, 0, 0, 7, 0, 32, 32);

	//Movement
	std::shared_ptr<Movement> movement = std::make_shared<Movement>(sprite, 200.f, 550.f, 20.f, *this); //speed for bullet set here
	addComponent(movement);

	std::shared_ptr<Attribute> attribute = std::make_shared<Attribute>(1, *this); //speed for bullet set here
	addComponent(attribute);
	attribute->range = 40;

	std::shared_ptr<bulletC> bullet = std::make_shared<bulletC>(x, y, velX, velY, texture, state, *this); //speed for bullet set here
	addComponent(bullet);

}

void Bullet::update(const float& dt, const sf::Vector2f mousePosView)
{
	Entity::update(dt, mousePosView);
}

void Bullet::render(sf::RenderTarget& target, sf::Shader* shader, sf::Vector2f light_position, const bool show_hitbox)
{
	Entity::render(target, shader, light_position, false);
}
