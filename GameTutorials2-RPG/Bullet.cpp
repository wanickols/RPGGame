#include "stdafx.h"
#include "Bullet.h"
#include "AnimationC.h"
#include "Movement.h"
#include "Hitbox.h"
#include "Attribute.h"
#include "physicsComponent.h"
#include "PhysicsDevice.h"
#include "bulletC.h"


Bullet::Bullet(float x, float y, float velX, float velY, sf::Texture& texture, const facing direction, std::shared_ptr<PhysicsDevice> p_device)
{
	GAME_PHYSICS physics(GAME_BODY_TYPE::GAME_DYNAMIC, GAME_OBJECT_SHAPE::GAME_CIRCLE, 12, 12, 1.f, 1.0f, 1.f, .1f, 1.f, 4.f, 0.f, 10.f, CATEGORY_BULLET, MASK_BULLET, true);
	physics.offSetX = 8;
	physics.offSetY = 48;


	std::shared_ptr<bulletC> bullet = std::make_shared<bulletC>(x, y, velX, velY, texture, direction, *this); //speed for bullet set here
	addComponent(bullet);

	//Animation
	std::shared_ptr<AnimationC> animation = std::make_shared<AnimationC>(sprite, texture, bullet->getStartPosition().x, bullet->getStartPosition().y, *this);
	addComponent(animation);
	getComponent<AnimationC>()->addAnimation("DEATH", 10.f, 0, 1, 3, 1, 32, 32);
	getComponent<AnimationC>()->addAnimation("ATTACK", 20.f, 0, 0, 7, 0, 32, 32);
	

	
	std::shared_ptr<physicsComponent> physicsC = std::make_shared<physicsComponent>(physics, p_device, *this); //itemComp for player set here
	addComponent(physicsC);

	//Hitbox
	std::shared_ptr<Hitbox> hitbox = std::make_shared<Hitbox>(sprite, 4.f, 2.f, 20.f, 20.f, *this); //hitbox for player set here
	addComponent(hitbox);

	

	//Movement
	std::shared_ptr<Movement> movement = std::make_shared<Movement>(sprite, sf::Vector2f(60.f, 60.f), sf::Vector2f(1.f, 1.f), sf::Vector2f(1.f, 1.f), *this); //speed for bullet set here
	addComponent(movement);

	std::shared_ptr<Attribute> attribute = std::make_shared<Attribute>(1, *this); //speed for bullet set here
	addComponent(attribute);
	attribute->range = 40;

	

}

void Bullet::update(const float& dt, const sf::Vector2f mousePosView)
{
	Entity::update(dt, mousePosView);
}

void Bullet::render(sf::RenderTarget& target, sf::Shader* shader, sf::Vector2f light_position, const bool show_hitbox)
{
	Entity::render(target, shader, light_position, false);
}
