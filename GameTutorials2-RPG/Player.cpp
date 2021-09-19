#include "stdafx.h"
#include "Player.h"
#include "Bullet.h"

//Init Functions
void Player::initVariables()
{
	attacking = false;
	if (!bulletTexture.loadFromFile("Resources/Images/Sprites/Bullets/FIRE_BULLET.png")) {
		throw "ERROR::GAME_STATE::COULD_NOT_LOAD_FIRE_BULLET_TEXTURE \n";
	}
}

void Player::initComponents()
{
	createMovementComponent(350.f, 1300.f, 400.f); //speed for player set here
	createHitBoxComponent(sprite, 12.f, 4.f, 41, 60);
}

//Constructors
Player::Player(float x, float y, sf::Texture& texture_sheet)
{
	initVariables();
	initComponents();

	setPosition(x, y);

	createAnimationComponent(texture_sheet); 
	creatAttributeComponent(1);
	animationComponent->addAnimation("DOWNIDLE", 15.f, 0, 0, 4, 0, 64, 64);
	animationComponent->addAnimation("UPIDLE", 15.f, 27, 0, 31, 0, 64, 64);
	animationComponent->addAnimation("RIGHTIDLE", 15.f, 9, 0, 13, 0, 64, 64);
	animationComponent->addAnimation("LEFTIDLE", 15.f, 18, 0, 22, 0, 64, 64);
	animationComponent->addAnimation("WALK_DOWN", 10.f, 0, 1, 3, 1, 64, 64);
	animationComponent->addAnimation("WALK_LEFT", 10.f, 4, 1, 7, 1, 64, 64);
	animationComponent->addAnimation("WALK_RIGHT", 10.f, 8, 1, 11, 1, 64, 64);
	animationComponent->addAnimation("WALK_UP", 10.f, 12, 1, 15, 1, 64, 64);
	//Idle Attack Animations
	animationComponent->addAnimation("IDLEATTACKDOWN", 6.f, 0, 2, 4, 2, 64, 64);
	animationComponent->addAnimation("IDLEATTACKINGDOWN", 6.f, 3, 2, 4, 2, 64, 64);
	animationComponent->addAnimation("IDLEATTACKUP", 6.f, 0, 3, 4, 3, 64, 64);
	animationComponent->addAnimation("IDLEATTACKINGUP", 6.f, 3, 3, 4, 3, 64, 64);
	animationComponent->addAnimation("IDLEATTACKRIGHT", 6.f, 0, 4, 4, 4, 64, 64);
	animationComponent->addAnimation("IDLEATTACKINGRIGHT", 6.f, 3, 4, 4, 4, 64, 64);
	animationComponent->addAnimation("IDLEATTACKLEFT", 6.f, 0, 5, 4, 5, 64, 64);
	animationComponent->addAnimation("IDLEATTACKINGLEFT", 6.f, 3, 5, 4, 5, 64, 64);

	animationComponent->addAnimation("MOVINGATTACKDOWN", 10.f, 5, 2, 8, 2, 64, 64);
	animationComponent->addAnimation("MOVINGATTACKUP", 10.f, 5, 3, 8, 3, 64, 64);
	animationComponent->addAnimation("MOVINGATTACKRIGHT", 10.f, 5, 4, 8, 4, 64, 64);
	animationComponent->addAnimation("MOVINGATTACKLEFT", 10.f, 5, 5, 8, 5, 64, 64);

}

Player::~Player()
{

}

std::shared_ptr<AttributeComponent> Player::getAttributeComponent()
{
	return attributeComponent;
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
	bullets.push_back(std::make_unique<Bullet>(this->getPosition().x, this->getPosition().y, this->movementComponent->getVelocity().x, this->movementComponent->getVelocity().y, bulletTexture, movementComponent->getLastState()));
}

//Functions
void Player::updateAnimation(const float& dt, const sf::Vector2f& mousePosView)
{
	if (movementComponent->getState(ATTACK)) {
		attacking = true;
		if (attacking) {
			if (movementComponent->getState(DOWNIDLE))
			{
				movementComponent->setLastState(DOWNIDLE);
				if (!animationComponent->getLastIsDone("IDLEATTACKDOWN"))
				{
					if (animationComponent->play("IDLEATTACKDOWN", dt, false)) {
						shoot(mousePosView);
					}
				}
				else {
					if (!animationComponent->play("IDLEATTACKINGDOWN", dt, false)) {
						
					}
					else {
						shoot(mousePosView);
						
						animationComponent->setIsDone("IDLEATTACKINGDOWN", false);
						attacking = false;
					}
				}
			}
			else if (movementComponent->getState(MOVING_DOWN))
			{
				movementComponent->setLastState(MOVING_DOWN);
				if (!animationComponent->play("MOVINGATTACKDOWN", dt, false)) {
					
				}
				else {
					shoot(mousePosView);
					animationComponent->setIsDone("MOVINGATTACKDOWN", false);
					attacking = false;

				}
			}
			else if (movementComponent->getState(UPIDLE))
			{
				movementComponent->setLastState(UPIDLE);
				if (!animationComponent->getLastIsDone("IDLEATTACKUP"))
				{
					if (animationComponent->play("IDLEATTACKUP", dt, false)) {
						shoot(mousePosView);
					}
				}
				else {
					if (!animationComponent->play("IDLEATTACKINGUP", dt, false)) {
						
					}
					else {
						
						shoot(mousePosView);
						animationComponent->setIsDone("IDLEATTACKINGUP", false);
						attacking = false;
					}
				}

			}
			else if (movementComponent->getState(MOVING_UP))
			{
				movementComponent->setLastState(MOVING_UP);
				if (!animationComponent->play("MOVINGATTACKUP", dt, false)) {
					
				}
				else {
					shoot(mousePosView);
					animationComponent->setIsDone("MOVINGATTACKUP", false);
					attacking = false;

				}
			}
			else if (movementComponent->getState(RIGHTIDLE))
			{
				movementComponent->setLastState(RIGHTIDLE);
				if (!animationComponent->getLastIsDone("IDLEATTACKRIGHT"))
				{
					if (animationComponent->play("IDLEATTACKRIGHT", dt, false)) {
						shoot(mousePosView);
					}
				}
				else {
					if (!animationComponent->play("IDLEATTACKINGRIGHT", dt, false)) {
					}
					else {
						shoot(mousePosView);
						animationComponent->setIsDone("IDLEATTACKINGRIGHT", false);
						attacking = false;
					}
				}

			}
			else if (movementComponent->getState(MOVING_RIGHT))
			{
				movementComponent->setLastState(MOVING_RIGHT);

				if (!animationComponent->play("MOVINGATTACKRIGHT", dt, false)) {
				
				}
				else {
					shoot(mousePosView);
					animationComponent->setIsDone("MOVINGATTACKRIGHT", false);
					attacking = false;

				}
			}
			else if (movementComponent->getState(LEFTIDLE))
			{
				movementComponent->setLastState(LEFTIDLE);
				if (!animationComponent->getLastIsDone("IDLEATTACKLEFT"))
				{
					if (animationComponent->play("IDLEATTACKLEFT", dt, false)) {
						shoot(mousePosView);
					}
				}
				else {
					if (!animationComponent->play("IDLEATTACKINGLEFT", dt, false)) {
		
					}
					else {
						shoot(mousePosView);
						animationComponent->setIsDone("IDLEATTACKINGLEFT", false);
						attacking = false;
					}
				}

			}
			else if (movementComponent->getState(MOVING_LEFT))
			{
				movementComponent->setLastState(MOVING_LEFT);
				if (!animationComponent->play("MOVINGATTACKLEFT", dt, false)) {
					
				}
				else {
					shoot(mousePosView);
					animationComponent->setIsDone("MOVINGATTACKLEFT", false);
					attacking = false;

				}
			}
			
		}
	}

	else {
		if (movementComponent->getState(DOWNIDLE))
		{
			movementComponent->setLastState(DOWNIDLE);
			animationComponent->play("DOWNIDLE", dt, false);
		}
		else if (movementComponent->getState(UPIDLE))
		{
			movementComponent->setLastState(UPIDLE);
			animationComponent->play("UPIDLE", dt, false);
		}
		else if (movementComponent->getState(LEFTIDLE))
		{
			movementComponent->setLastState(LEFTIDLE);
			animationComponent->play("LEFTIDLE", dt, false);
		}
		else if (movementComponent->getState(RIGHTIDLE))
		{
			movementComponent->setLastState(RIGHTIDLE);
			animationComponent->play("RIGHTIDLE", dt, false);
		}
		else if (movementComponent->getState(MOVING_LEFT))
		{
			movementComponent->setLastState(MOVING_LEFT);
			animationComponent->play("WALK_LEFT", dt, movementComponent->getVelocity().x, movementComponent->getMaxVelocity(), false);
		}
		else if (movementComponent->getState(MOVING_RIGHT))
		{
			movementComponent->setLastState(MOVING_RIGHT);
			animationComponent->play("WALK_RIGHT", dt, movementComponent->getVelocity().x, movementComponent->getMaxVelocity(), false);
		}
		else if (movementComponent->getState(MOVING_UP))
		{
			movementComponent->setLastState(MOVING_UP);
			animationComponent->play("WALK_UP", dt, movementComponent->getVelocity().y, movementComponent->getMaxVelocity(), false);
		}
		else if (movementComponent->getState(MOVING_DOWN))
		{
			movementComponent->setLastState(MOVING_DOWN);
			animationComponent->play("WALK_DOWN", dt, movementComponent->getVelocity().y, movementComponent->getMaxVelocity(), false);
		}
	}
}

void Player::update(const float& dt, const sf::Vector2f& mousePosView)
{
	movementComponent->update(dt);
	//Bullets
	if (!bullets.empty()) {
		auto iter = bullets.begin();
		while (iter != bullets.end())
		{
			if (iter->get()->getRunning()) {
				iter->get()->update(dt, mousePosView);
				iter++;
			}
			else
				iter = bullets.erase(iter);
		}
	}
	else {
		animationComponent->setIsDone("IDLEATTACKDOWN", false);
		animationComponent->setIsDone("IDLEATTACKUP", false);
		animationComponent->setIsDone("IDLEATTACKLEFT", false);
		animationComponent->setIsDone("IDLEATTACKRIGHT", false);
	}
		
	updateAnimation(dt, mousePosView);
	
	hitBoxComponent->update();
	
	
	//addExp(20);
	//system("cls");
	//std::cout << attributeComponent->debugPrint();
	
}

void Player::render(sf::RenderTarget& target, sf::Shader* shader, const bool show_hitbox)
{
	if (shader) {
		shader->setUniform("hasTexture", true);
		shader->setUniform("lightPos", this->getCenterPosition());

		target.draw(sprite, shader);
		for (auto& iter : bullets)
		{
			if (iter->getRunning())
				iter->render(target);
		}
	}
	else
		target.draw(sprite);
	if(show_hitbox)
		hitBoxComponent->render(target);

}



