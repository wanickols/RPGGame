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
	animationComponent->addAnimation("WALK_DOWN", 8.f, 0, 1, 3, 1, 64, 64);
	animationComponent->addAnimation("WALK_LEFT", 8.f, 4, 1, 7, 1, 64, 64);
	animationComponent->addAnimation("WALK_RIGHT", 8.f, 8, 1, 11, 1, 64, 64);
	animationComponent->addAnimation("WALK_UP", 8.f, 12, 1, 15, 1, 64, 64);
	animationComponent->addAnimation("ATTACKDOWN", 6.f, 0, 2, 4, 2, 64, 64);
	animationComponent->addAnimation("ATTACKINGDOWN", 6.f, 3, 2, 4, 2, 64, 64);
	animationComponent->addAnimation("ATTACKUP", 6.f, 0, 3, 4, 3, 64, 64);
	animationComponent->addAnimation("ATTACKINGUP", 6.f, 3, 3, 4, 3, 64, 64);
	animationComponent->addAnimation("ATTACKRIGHT", 6.f, 0, 4, 4, 4, 64, 64);
	animationComponent->addAnimation("ATTACKINGRIGHT", 6.f, 3, 4, 4, 4, 64, 64);
	animationComponent->addAnimation("ATTACKLEFT", 6.f, 0, 5, 4, 5, 64, 64);
	animationComponent->addAnimation("ATTACKINGLEFT", 6.f, 3, 5, 4, 5, 64, 64);

	
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
			if (movementComponent->getState(DOWNIDLE) || movementComponent->getState(MOVING_DOWN))
			{
				if (!animationComponent->getLastIsDone("ATTACKDOWN"))
				{
					if (animationComponent->play("ATTACKDOWN", dt, false)) {
						shoot(mousePosView);
					}
				}
				else {
					if (!animationComponent->play("ATTACKINGDOWN", dt, false)) {
						movementComponent->setLastState(DOWNIDLE);
					}
					else {
						shoot(mousePosView);
						animationComponent->setIsDone("ATTACKINGDOWN", false);
						attacking = false;
					}
				}
			}
			else if (movementComponent->getState(UPIDLE) || movementComponent->getState(MOVING_UP))
			{
				if (!animationComponent->getLastIsDone("ATTACKUP"))
				{
					if (animationComponent->play("ATTACKUP", dt, false)) {
						shoot(mousePosView);
					}
				}
				else {
					if (!animationComponent->play("ATTACKINGUP", dt, false)) {
						
					}
					else {
						movementComponent->setLastState(UPIDLE);
						shoot(mousePosView);
						animationComponent->setIsDone("ATTACKINGUP", false);
						attacking = false;
					}
				}

			}
			else if (movementComponent->getState(RIGHTIDLE) || movementComponent->getState(MOVING_RIGHT))
			{
				if (!animationComponent->getLastIsDone("ATTACKRIGHT"))
				{
					if (animationComponent->play("ATTACKRIGHT", dt, false)) {
						shoot(mousePosView);
					}
				}
				else {
					if (!animationComponent->play("ATTACKINGRIGHT", dt, false)) {

					}
					else {
						movementComponent->setLastState(RIGHTIDLE);
						shoot(mousePosView);
						animationComponent->setIsDone("ATTACKINGRIGHT", false);
						attacking = false;
					}
				}

			}
			else if (movementComponent->getState(LEFTIDLE) || movementComponent->getState(MOVING_LEFT))
			{
				if (!animationComponent->getLastIsDone("ATTACKLEFT"))
				{
					if (animationComponent->play("ATTACKLEFT", dt, false)) {
						shoot(mousePosView);
					}
				}
				else {
					if (!animationComponent->play("ATTACKINGLEFT", dt, false)) {
						movementComponent->setLastState(LEFTIDLE);
					}
					else {
						shoot(mousePosView);
						animationComponent->setIsDone("ATTACKINGLEFT", false);
						attacking = false;
					}
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
		animationComponent->setIsDone("ATTACKDOWN", false);
		animationComponent->setIsDone("ATTACKUP", false);
		animationComponent->setIsDone("ATTACKLEFT", false);
		animationComponent->setIsDone("ATTACKRIGHT", false);
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



