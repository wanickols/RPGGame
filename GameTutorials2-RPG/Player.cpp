#include "stdafx.h"
#include "Player.h"
#include "Bullet.h"
#include "TileMap.h"
#include "FireRune.h"
#include "HitboxComponent.h"
#include "MovementComponent.h"
#include "AnimationComponent.h"
#include "AttributeComponent.h"
#include "InputComponent.h"
#include "SkillComponent.h"
#include "Component.h"



//Init Functions
void Player::initVariables()
{
	

	if (!bullet_shader.loadFromFile("vertex_shader.vert", "bullet_shader.frag"))
	{
		std::cout << "ERROR::PLAYER::COULD_NOT_LOAD_BULLET_SHADER" << "\n";
	}

}

void Player::initComponents()
{
	//movement
	std::shared_ptr<MovementComponent> movementComponent = std::make_shared<MovementComponent>(sprite, 250.f, 1300.f, 400.f, this); //speed for player set here
	addComponent(movementComponent);
	//hitbox
	std::shared_ptr<HitboxComponent> hitboxComponent = std::make_shared<HitboxComponent>(sprite, 12.f, 0.f, 41.f, 42.f, this); //hitbox for player set here
	addComponent(hitboxComponent);
	//Input
	std::shared_ptr<InputComponent> inputComponent = std::make_shared<InputComponent>(this); //hitbox for player set here
	addComponent(inputComponent);
	//Skill
	addComponent(std::make_shared<SkillComponent>(this)); //Skills
	//attribute
	std::shared_ptr<AttributeComponent> attributeComponent = std::make_shared<AttributeComponent>(1, this); //hitbox for player set here
	addComponent(attributeComponent);

}

void Player::initAnimations(sf::Texture& texture_sheet)
{
	std::shared_ptr<AnimationComponent> animationComponent = std::make_shared<AnimationComponent>(sprite, texture_sheet, this);
	addComponent(animationComponent);
	

	getComponent<AnimationComponent>()->addAnimation("DOWNIDLE", 15.f, 0, 0, 4, 0, 64, 64);
	getComponent<AnimationComponent>()->addAnimation("UPIDLE", 15.f, 27, 0, 31, 0, 64, 64);
	getComponent<AnimationComponent>()->addAnimation("RIGHTIDLE", 15.f, 9, 0, 13, 0, 64, 64);
	getComponent<AnimationComponent>()->addAnimation("LEFTIDLE", 15.f, 18, 0, 22, 0, 64, 64);
	getComponent<AnimationComponent>()->addAnimation("WALK_DOWN", 8.f, 0, 1, 3, 1, 64, 64);
	getComponent<AnimationComponent>()->addAnimation("WALK_LEFT", 8.f, 4, 1, 7, 1, 64, 64);
	getComponent<AnimationComponent>()->addAnimation("WALK_RIGHT", 8.f, 8, 1, 11, 1, 64, 64);
	getComponent<AnimationComponent>()->addAnimation("WALK_UP", 8.f, 12, 1, 15, 1, 64, 64);
	//Idle Attack Animations
	getComponent<AnimationComponent>()->addAnimation("IDLEATTACKDOWN", 6.f, 0, 2, 4, 2, 64, 64);
	getComponent<AnimationComponent>()->addAnimation("IDLEATTACKINGDOWN", 6.f, 3, 2, 4, 2, 64, 64);
	getComponent<AnimationComponent>()->addAnimation("IDLEATTACKUP", 6.f, 0, 3, 4, 3, 64, 64);
	getComponent<AnimationComponent>()->addAnimation("IDLEATTACKINGUP", 6.f, 3, 3, 4, 3, 64, 64);
	getComponent<AnimationComponent>()->addAnimation("IDLEATTACKRIGHT", 6.f, 0, 4, 4, 4, 64, 64);
	getComponent<AnimationComponent>()->addAnimation("IDLEATTACKINGRIGHT", 6.f, 3, 4, 4, 4, 64, 64);
	getComponent<AnimationComponent>()->addAnimation("IDLEATTACKLEFT", 6.f, 0, 5, 4, 5, 64, 64);
	getComponent<AnimationComponent>()->addAnimation("IDLEATTACKINGLEFT", 6.f, 3, 5, 4, 5, 64, 64);

	getComponent<AnimationComponent>()->addAnimation("MOVINGATTACKDOWN", 8.f, 5, 2, 8, 2, 64, 64);
	getComponent<AnimationComponent>()->addAnimation("MOVINGATTACKUP", 8.f, 5, 3, 8, 3, 64, 64);
	getComponent<AnimationComponent>()->addAnimation("MOVINGATTACKRIGHT", 8.f, 5, 4, 8, 4, 64, 64);
	getComponent<AnimationComponent>()->addAnimation("MOVINGATTACKLEFT", 8.f, 5, 5, 8, 5, 64, 64);

}

void Player::initRunes()
{
	runes.push_back(std::make_shared<FireRune>());
	activeRune = runes.at(0);
}

//Constructors
Player::Player(float x, float y, sf::Texture& texture_sheet)
{
	initVariables();
	initRunes();
	initAnimations(texture_sheet);
	initComponents();
	setPosition(x, y);
	
}

Player::~Player()
{

}

const std::shared_ptr<Rune> Player::getActiveRune()
{
	return activeRune;
}

void Player::updateBulletCollision(const float& dt, std::shared_ptr<TileMap> map)
{

	activeRune->updateBulletCollision(dt, map);
}

//Functions
void Player::updateAnimation(const float& dt, const sf::Vector2f mousePosView)
{
	
	
}

void Player::update(const float& dt, const sf::Vector2f mousePosView)
{
	activeRune->update(dt, mousePosView);
	Entity::update(dt, mousePosView);
	//Bullets
	//Checks if there are bullets on the screen to know if keep arms up or put them down
	if (activeRune->isBulletEmpty()) {
		getComponent<AnimationComponent>()->setIsDone("IDLEATTACKDOWN", false);
		getComponent<AnimationComponent>()->setIsDone("IDLEATTACKUP", false);
		getComponent<AnimationComponent>()->setIsDone("IDLEATTACKLEFT", false);
		getComponent<AnimationComponent>()->setIsDone("IDLEATTACKRIGHT", false);
	}
		
	updateAnimation(dt, mousePosView);
	
	
	std::cout << getComponent<SkillComponent>()->getSkillLvl("Endurance") << "\n";

	
	//addExp(20);
	//system("cls");
	//std::cout << attributeComponent->debugPrint();
	
}

void Player::render(sf::RenderTarget& target, sf::Shader* shader, sf::Vector2f light_position, const bool show_hitbox)
{
	Entity::render(target, shader, light_position, true);
	if (shader) {
		shader->setUniform("hasTexture", true);
		shader->setUniform("lightPos", getCenterPosition());
		
		target.draw(sprite, shader);
		activeRune->render(target, &bullet_shader, light_position, false);
	}
	else {
		target.draw(sprite);
		activeRune->render(target);
	}


}



