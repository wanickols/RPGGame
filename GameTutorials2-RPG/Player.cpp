#include "stdafx.h"
#include "Player.h"
#include "Bullet.h"
#include "TileMap.h"
#include "FireRune.h"
#include "Inventory.h"
#include "ComponentInclude.h"
#include "itemComponentInlcudes.h"
#include "ItemLibrary.h"
#include "Constants.h"



//Init Functions
void Player::initVariables()
{
	

	if (!bullet_shader.loadFromFile("vertex_shader.vert", "bullet_shader.frag"))
	{
		std::cout << "ERROR::PLAYER::COULD_NOT_LOAD_BULLET_SHADER" << "\n";
	}

	attack = false;
	
	
}

void Player::initComponents()
{
	//movement
	std::shared_ptr<Movement> movement = std::make_shared<Movement>(sprite, sf::Vector2f(4.f,15.f), sf::Vector2f(4.0f,4.0f), sf::Vector2f(1.1f,1.1f), *this); //speed for player set here
	addComponent(movement);
	//hitbox
	//std::shared_ptr<Hitbox> hitbox = std::make_shared<Hitbox>(sprite, 12.f, 0.f, 41.f, 42.f, *this); //hitbox for player set here
	//addComponent(hitbox);
	//Input
	std::shared_ptr<UserInput> input = std::make_shared<UserInput>(*this); //hitbox for player set here
	addComponent(input);
	//Skill
	addComponent(std::make_shared<Skills>(*this)); //Skills
	//attribute
	std::shared_ptr<Attribute> attribute = std::make_shared<Attribute>(1, *this); //attribute for player set here
	attribute->EntityName = "player";
	addComponent(attribute);

	std::cout << attribute->debugPrint();

	std::shared_ptr<Combat> combat = std::make_shared<Combat>(*this); //combat for player set here
	addComponent(combat);

	std::shared_ptr<ItemComp> itemC = std::make_shared<ItemComp>(*this); //itemComp for player set here
	addComponent(itemC);

	
}

void Player::initPhysics(std::shared_ptr<PhysicsDevice> p_Device)
{
	GAME_PHYSICS physics(GAME_BODY_TYPE::GAME_DYNAMIC, GAME_OBJECT_SHAPE::GAME_RECTANGLE, 20, 32, 4.f, 0.0f, .7f, .1f, 8.f, 1.f, 0.f, 10.f, CATEGORY_PLAYER, MASK_PLAYER);
	physics.offSetY = 12;
	physics.offSetX = -4;

	std::shared_ptr<physicsComponent> physicsC = std::make_shared<physicsComponent>(physics, p_Device, *this); //itemComp for player set here

	addComponent(physicsC);
}

void Player::initAnimations(sf::Texture& texture_sheet, float x, float y)
{
	

	std::shared_ptr<AnimationC> animation = std::make_shared<AnimationC>(sprite, texture_sheet, x,y, *this);
	addComponent(animation);
	

	getComponent<AnimationC>()->addAnimation("DOWNIDLE", 15.f, 0, 0, 4, 0, 64, 64);
	getComponent<AnimationC>()->addAnimation("UPIDLE", 15.f, 27, 0, 31, 0, 64, 64);
	getComponent<AnimationC>()->addAnimation("RIGHTIDLE", 15.f, 9, 0, 13, 0, 64, 64);
	getComponent<AnimationC>()->addAnimation("LEFTIDLE", 15.f, 18, 0, 22, 0, 64, 64);
	getComponent<AnimationC>()->addAnimation("WALKDOWN", 8.f, 0, 1, 3, 1, 64, 64);
	getComponent<AnimationC>()->addAnimation("WALKLEFT", 8.f, 4, 1, 7, 1, 64, 64);
	getComponent<AnimationC>()->addAnimation("WALKRIGHT", 8.f, 8, 1, 11, 1, 64, 64);
	getComponent<AnimationC>()->addAnimation("WALKUP", 8.f, 12, 1, 15, 1, 64, 64);
	//Idle Attack Animations
	getComponent<AnimationC>()->addAnimation("IDLEATTACKDOWN", 6.f, 0, 2, 4, 2, 64, 64);
	getComponent<AnimationC>()->addAnimation("IDLEATTACKINGDOWN", 6.f, 3, 2, 4, 2, 64, 64);
	getComponent<AnimationC>()->addAnimation("IDLEATTACKUP", 6.f, 0, 3, 4, 3, 64, 64);
	getComponent<AnimationC>()->addAnimation("IDLEATTACKINGUP", 6.f, 3, 3, 4, 3, 64, 64);
	getComponent<AnimationC>()->addAnimation("IDLEATTACKRIGHT", 6.f, 0, 4, 4, 4, 64, 64);
	getComponent<AnimationC>()->addAnimation("IDLEATTACKINGRIGHT", 6.f, 3, 4, 4, 4, 64, 64);
	getComponent<AnimationC>()->addAnimation("IDLEATTACKLEFT", 6.f, 0, 5, 4, 5, 64, 64);
	getComponent<AnimationC>()->addAnimation("IDLEATTACKINGLEFT", 6.f, 3, 5, 4, 5, 64, 64);

	getComponent<AnimationC>()->addAnimation("MOVINGATTACKDOWN", 8.f, 5, 2, 8, 2, 64, 64);
	getComponent<AnimationC>()->addAnimation("MOVINGATTACKUP", 8.f, 5, 3, 8, 3, 64, 64);
	getComponent<AnimationC>()->addAnimation("MOVINGATTACKRIGHT", 8.f, 5, 4, 8, 4, 64, 64);
	getComponent<AnimationC>()->addAnimation("MOVINGATTACKLEFT", 8.f, 5, 5, 8, 5, 64, 64);

}

void Player::initRunes()
{
	
}

void Player::initItems(std::shared_ptr<ItemLibrary> item_lib)
{
	itemComp = getComponent<ItemComp>();
	itemComp->initLibrary(item_lib);
	itemComp->addItem("FireRune", true);
}

//Constructors
Player::Player(float x, float y, sf::Texture& texture_sheet, std::shared_ptr<PhysicsDevice> p_Device)
{
	initVariables();
	initAnimations(texture_sheet, x, y);
	initPhysics(p_Device);
	initComponents();
	
}

Player::~Player()
{

}

const std::shared_ptr<Item> Player::getActiveRune()
{
	return getComponent<ItemComp>()->activeRune;
}

void Player::updateBulletCollision(const float& dt, std::shared_ptr<TileMap> map)
{
	//getComponent<ItemComp>()->activeRune->getItemComponent<RuneComponent>()->updateBulletCollision(dt, map);
}

//Functions
void Player::update(const float& dt, const sf::Vector2f mousePosView)
{
	getComponent<ItemComp>()->activeRune->update(dt, mousePosView, getCenterPosition());
	//components
	Entity::update(dt, mousePosView);
	
	//Rune
	//Checks if there are bullets on the screen to know if keep arms up or put them down
	if (getComponent<ItemComp>()->activeRune->getItemComponent<RuneComponent>()->isBulletEmpty()) {
		getComponent<AnimationC>()->setIsDone("IDLEATTACKDOWN", false);
		getComponent<AnimationC>()->setIsDone("IDLEATTACKUP", false);
		getComponent<AnimationC>()->setIsDone("IDLEATTACKLEFT", false);
		getComponent<AnimationC>()->setIsDone("IDLEATTACKRIGHT", false);
	}
	
	//Debug
	//std::cout << getComponent<Skills>()->getSkillLvl("Endurance") << "\n";

	
	//addExp(20);
	//system("cls");
	//std::cout << Attribute->debugPrint();
	
}

void Player::render(sf::RenderTarget& target, sf::Shader* shader, sf::Vector2f light_position, const bool show_hitbox)
{
	//components
	Entity::render(target, shader, light_position, false);
	
	//Rune
	if (shader) {
		getComponent<ItemComp>()->activeRune->render(target, &bullet_shader, light_position, false);
	}
	else {
		getComponent<ItemComp>()->activeRune->render(target);
	}


}

const bool Player::getAttack()
{
	return this->attack;
}

void Player::setAttack(bool attacking)
{
	attack = attacking;
}



