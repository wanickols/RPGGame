#include "stdafx.h"
#include "Player.h"
#include "Bullet.h"
#include "TileMap.h"
#include "FireRune.h"

//Init Functions
void Player::initVariables()
{
	attacking = false;

	if (!bullet_shader.loadFromFile("vertex_shader.vert", "bullet_shader.frag"))
	{
		std::cout << "ERROR::PLAYER::COULD_NOT_LOAD_BULLET_SHADER" << "\n";
	}

}

void Player::initComponents()
{
	

	createMovementComponent(250.f, 1300.f, 400.f); //speed for player set here
	createHitBoxComponent(sprite, 12.f, 0.f, 41, 42);
	createSkillComponent();
	creatAttributeComponent(1);
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
	initComponents();
	initAnimations(texture_sheet);
	initRunes();

	setPosition(x, y);
	
}

Player::~Player()
{

}

std::shared_ptr<AttributeComponent> Player::getAttributeComponent()
{
	return attributeComponent;
}

const facing Player::getDirection() const
{
	return movementComponent->getDirection();
}

void Player::setDirection(facing new_direction)
{
	movementComponent->setDirection(new_direction);
}

void Player::loseHealth(const int health)
{
	attributeComponent->hp -= health;
	attributeComponent->healthUpdate = true;
	if (attributeComponent->hp < 0)
		attributeComponent->hp = 0;
}

void Player::addHealth(const int health)
{
	attributeComponent->hp += health;
	attributeComponent->healthUpdate = true;
	if (attributeComponent->hp > attributeComponent->hpMax)
		attributeComponent->hp = attributeComponent->hpMax;
}

void Player::loseEnergy(const int energy)
{
	attributeComponent->energy -= energy;
	attributeComponent->energyUpdate = true;
	if (attributeComponent->energy < 0)
		attributeComponent->energy = 0;
}

void Player::addEnergy(const int energy)
{
	attributeComponent->energy += energy;
	attributeComponent->energyUpdate = true;
	if (attributeComponent->energy > attributeComponent->energyMax)
		attributeComponent->energy = attributeComponent->energyMax;
}

void Player::loseExp(const int exp)
{
	attributeComponent->exp -= exp;
	if (attributeComponent->exp < 0)
		attributeComponent->exp = 0;
}

void Player::addExp(const int exp)
{
	attributeComponent->addExp(exp);
}

void Player::shoot(const sf::Vector2f& mousePosView)
{
	attacking = false;
	activeRune->shoot(getPosition().x, getPosition().y, movementComponent->getVelocity().x + (mousePosView.x - getPosition().x)/100, movementComponent->getVelocity().y + (mousePosView.y - getPosition().y)/100, movementComponent->getLastState());
}

void Player::updateBulletCollision(const float& dt, std::shared_ptr<TileMap> map)
{

	activeRune->updateBulletCollision(dt, map);
}

//Functions
void Player::updateAnimation(const float& dt, const sf::Vector2f mousePosView)
{
	if (movementComponent->getState(ATTACK)) {
		attacking = true;
		if (attacking) {
			switch (movementComponent->getLastState())
			{
			case(DOWNIDLE):
				movementComponent->setLastState(DOWNIDLE);
				if (!getComponent<AnimationComponent>()->getLastIsDone("IDLEATTACKDOWN"))
				{
					if (getComponent<AnimationComponent>()->play("IDLEATTACKDOWN", dt, false)) {
						shoot(mousePosView);
					}
				}
				else {
					if (!getComponent<AnimationComponent>()->play("IDLEATTACKINGDOWN", dt, false)) {
						
					}
					else {
						shoot(mousePosView);
						getComponent<AnimationComponent>()->setIsDone("IDLEATTACKINGDOWN", false);
					}
				}
				break;
			case(MOVING_DOWN):
				movementComponent->setLastState(MOVING_DOWN);
				if (!getComponent<AnimationComponent>()->play("MOVINGATTACKDOWN", dt, false)) {
				
				}
				else {
					shoot(mousePosView);
					getComponent<AnimationComponent>()->setIsDone("MOVINGATTACKDOWN", false);
				}
				break;
			case(UPIDLE):
				movementComponent->setLastState(UPIDLE);
				if (!getComponent<AnimationComponent>()->getLastIsDone("IDLEATTACKUP"))
				{
					if (getComponent<AnimationComponent>()->play("IDLEATTACKUP", dt, false)) {
						shoot(mousePosView);
					}
				}
				else {
					if (!getComponent<AnimationComponent>()->play("IDLEATTACKINGUP", dt, false)) {

					}
					else {

						shoot(mousePosView);
						getComponent<AnimationComponent>()->setIsDone("IDLEATTACKINGUP", false);
					}
				}
				break;
			case(MOVING_UP):
				movementComponent->setLastState(MOVING_UP);
				if (!getComponent<AnimationComponent>()->play("MOVINGATTACKUP", dt, false)) {
					
				}
				else {
					shoot(mousePosView);
					getComponent<AnimationComponent>()->setIsDone("MOVINGATTACKUP", false);

				}
				break;
			case(RIGHTIDLE):
				movementComponent->setLastState(RIGHTIDLE);
				if (!getComponent<AnimationComponent>()->getLastIsDone("IDLEATTACKRIGHT"))
				{
					if (getComponent<AnimationComponent>()->play("IDLEATTACKRIGHT", dt, false)) {
						shoot(mousePosView);
					}
				}
				else {
					if (!getComponent<AnimationComponent>()->play("IDLEATTACKINGRIGHT", dt, false)) {
					}
					else {
						shoot(mousePosView);
						getComponent<AnimationComponent>()->setIsDone("IDLEATTACKINGRIGHT", false);
					}
				}
				break;
			case(MOVING_RIGHT):
				movementComponent->setLastState(MOVING_RIGHT);
				if (!getComponent<AnimationComponent>()->play("MOVINGATTACKRIGHT", dt, false)) {
				
				}
				else {
					shoot(mousePosView);
					getComponent<AnimationComponent>()->setIsDone("MOVINGATTACKRIGHT", false);

				}
			
				break;
			case(LEFTIDLE):
				movementComponent->setLastState(LEFTIDLE);
				if (!getComponent<AnimationComponent>()->getLastIsDone("IDLEATTACKLEFT"))
				{
					if (getComponent<AnimationComponent>()->play("IDLEATTACKLEFT", dt, false)) {
						shoot(mousePosView);
					}
				}
				else {
					if (!getComponent<AnimationComponent>()->play("IDLEATTACKINGLEFT", dt, false)) {
					}
					else {
						shoot(mousePosView);
						getComponent<AnimationComponent>()->setIsDone("IDLEATTACKINGLEFT", false);
					}
				}
				break;
			case(MOVING_LEFT):
				movementComponent->setLastState(MOVING_LEFT);
				if (!getComponent<AnimationComponent>()->play("MOVINGATTACKLEFT", dt, false)) {

				}
				else {
					shoot(mousePosView);
					getComponent<AnimationComponent>()->setIsDone("MOVINGATTACKLEFT", false);
				}
				break;
			
			}
		}
		movementComponent->getState();
	}
	else {
	//ANIMATIONS WHILE NOT ATTACKING
		switch (movementComponent->getState())
		{	
		case(DOWNIDLE):
			getComponent<AnimationComponent>()->play("DOWNIDLE", dt, false);
			break;
		case(UPIDLE):
			getComponent<AnimationComponent>()->play("UPIDLE", dt, false);
			break;
		case(LEFTIDLE):
			getComponent<AnimationComponent>()->play("LEFTIDLE", dt, false);
			break;
		case(RIGHTIDLE):
			getComponent<AnimationComponent>()->play("RIGHTIDLE", dt, false);
			break;
		case(MOVING_LEFT):
			getComponent<AnimationComponent>()->play("WALK_LEFT", dt, movementComponent->getVelocity().x, movementComponent->getMaxVelocity(), false);
			break;
		case(MOVING_RIGHT):
			getComponent<AnimationComponent>()->play("WALK_RIGHT", dt, movementComponent->getVelocity().x, movementComponent->getMaxVelocity(), false);
			break;
		case(MOVING_UP):
			getComponent<AnimationComponent>()->play("WALK_UP", dt, movementComponent->getVelocity().y, movementComponent->getMaxVelocity(), false);
			break;
		case(MOVING_DOWN):
			getComponent<AnimationComponent>()->play("WALK_DOWN", dt, movementComponent->getVelocity().y, movementComponent->getMaxVelocity(), false);
			break;
		}
	}
}

void Player::update(const float& dt, const sf::Vector2f mousePosView)
{
	
	movementComponent->update(dt);
	activeRune->update(dt, mousePosView);
	//Bullets
	//Checks if there are bullets on the screen to know if keep arms up or put them down
	if (activeRune->isBulletEmpty()) {
		getComponent<AnimationComponent>()->setIsDone("IDLEATTACKDOWN", false);
		getComponent<AnimationComponent>()->setIsDone("IDLEATTACKUP", false);
		getComponent<AnimationComponent>()->setIsDone("IDLEATTACKLEFT", false);
		getComponent<AnimationComponent>()->setIsDone("IDLEATTACKRIGHT", false);
	}
		
	updateAnimation(dt, mousePosView);
	
	hitBoxComponent->update();
	
	std::cout << skillComponent->getSkillLvl("Endurance") << "\n";

	
	//addExp(20);
	//system("cls");
	//std::cout << attributeComponent->debugPrint();
	
}

void Player::render(sf::RenderTarget& target, sf::Shader* shader, sf::Vector2f light_position, const bool show_hitbox)
{
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
	if(show_hitbox)
		hitBoxComponent->render(target);

}



