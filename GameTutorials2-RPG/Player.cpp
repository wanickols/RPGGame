#include "stdafx.h"
#include "Player.h"
#include "Bullet.h"
#include "TileMap.h"
#include "FireRune.h"
#include "Hitbox.h"
#include "Movement.h"
#include "AnimationC.h"
#include "Attribute.h"
#include "UserInput.h"
#include "Skills.h"
#include "Component.h"
#include "Inventory.h"
#include "itemComponentInlcudes.h"



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
	std::shared_ptr<Movement> movement = std::make_shared<Movement>(sprite, 250.f, 1300.f, 400.f, this); //speed for player set here
	addComponent(movement);
	//hitbox
	std::shared_ptr<Hitbox> hitbox = std::make_shared<Hitbox>(sprite, 12.f, 0.f, 41.f, 42.f, this); //hitbox for player set here
	addComponent(hitbox);
	//Input
	std::shared_ptr<UserInput> input = std::make_shared<UserInput>(this); //hitbox for player set here
	addComponent(input);
	//Skill
	addComponent(std::make_shared<Skills>(this)); //Skills
	//attribute
	std::shared_ptr<Attribute> attribute = std::make_shared<Attribute>(1, this); //hitbox for player set here
	addComponent(attribute);

}

void Player::initAnimations(sf::Texture& texture_sheet, float x, float y)
{
	std::shared_ptr<AnimationC> animation = std::make_shared<AnimationC>(sprite, texture_sheet, x,y, this);
	addComponent(animation);
	

	getComponent<AnimationC>()->addAnimation("DOWNIDLE", 15.f, 0, 0, 4, 0, 64, 64);
	getComponent<AnimationC>()->addAnimation("UPIDLE", 15.f, 27, 0, 31, 0, 64, 64);
	getComponent<AnimationC>()->addAnimation("RIGHTIDLE", 15.f, 9, 0, 13, 0, 64, 64);
	getComponent<AnimationC>()->addAnimation("LEFTIDLE", 15.f, 18, 0, 22, 0, 64, 64);
	getComponent<AnimationC>()->addAnimation("WALK_DOWN", 8.f, 0, 1, 3, 1, 64, 64);
	getComponent<AnimationC>()->addAnimation("WALK_LEFT", 8.f, 4, 1, 7, 1, 64, 64);
	getComponent<AnimationC>()->addAnimation("WALK_RIGHT", 8.f, 8, 1, 11, 1, 64, 64);
	getComponent<AnimationC>()->addAnimation("WALK_UP", 8.f, 12, 1, 15, 1, 64, 64);
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
	//FireRune
	std::shared_ptr<Item> fr = std::make_shared<Item>();
	std::shared_ptr<ItemInfo> info = std::make_shared<ItemInfo>(0, "Fire Rune",
		"A fiery red stone hot to the touch and incredibely dense. \n Its origin is unknown, but it enables the user to shoot fire when placed in his hand.",//description
		ItemRarity::Unique, ItemClasses::RUNE, *fr); //Info
	fr->addItemComponent(info);

	std::shared_ptr<Weapon> weapon = std::make_shared<Weapon>(25, 20, 25, 2, *fr, "Resources/Images/Sprites/Items/Firerune.png");
	fr->addItemComponent(weapon);

	std::shared_ptr<RuneComponent> runeComp = std::make_shared<RuneComponent>("Resources/Images/Sprites/Bullets/FIRE_BULLET.png", *fr);
	fr->addItemComponent(runeComp);
	runes.push_back(fr);

	activeRune = runes.at(0);

	getComponent<Attribute>()->range = activeRune->getItemComponent<Weapon>()->getRange();

	inventory = std::make_shared<Inventory>(32);
	std::cout << "Inv: Before" << inventory->maxSize() << inventory->size() << std::endl;
	inventory->add(fr.get());
	inventory->remove(0);
	std::cout << "Inv: After" << inventory->maxSize() << inventory->size() << std::endl;
}

//Constructors
Player::Player(float x, float y, sf::Texture& texture_sheet)
{
	initVariables();
	initAnimations(texture_sheet, x, y);
	initComponents();
	initRunes();
	

}

Player::~Player()
{

}

const std::shared_ptr<Item> Player::getActiveRune()
{
	return activeRune;
}

void Player::updateBulletCollision(const float& dt, std::shared_ptr<TileMap> map)
{
	activeRune->getItemComponent<RuneComponent>()->updateBulletCollision(dt, map);
}

//Functions
void Player::update(const float& dt, const sf::Vector2f mousePosView)
{
	activeRune->update(dt, mousePosView, getCenterPosition());
	//components
	Entity::update(dt, mousePosView);
	
	//Rune
	//Checks if there are bullets on the screen to know if keep arms up or put them down
	if (activeRune->getItemComponent<RuneComponent>()->isBulletEmpty()) {
		getComponent<AnimationC>()->setIsDone("IDLEATTACKDOWN", false);
		getComponent<AnimationC>()->setIsDone("IDLEATTACKUP", false);
		getComponent<AnimationC>()->setIsDone("IDLEATTACKLEFT", false);
		getComponent<AnimationC>()->setIsDone("IDLEATTACKRIGHT", false);
	}
	
	//Debug
	std::cout << getComponent<Skills>()->getSkillLvl("Endurance") << "\n";

	
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
		activeRune->render(target, &bullet_shader, light_position, false);
	}
	else {
		activeRune->render(target);
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



