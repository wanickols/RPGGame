#pragma once
#include "Entity.h"

class Bullet;
class FireRune;
class Rune;
class TileMap;
class Inventory;
class Item;
class ItemLibrary;
class ItemComp;
class PhysicsDevice;

class Player :
	public Entity
{
private:
	//Init Functions
	void initVariables();
	void initComponents();
	void initPhysics(std::shared_ptr<PhysicsDevice> p_Device);
	void initAnimations(sf::Texture& texture_sheet, float x, float y);
public:
	void initRunes();
	void initItems(std::shared_ptr<ItemLibrary> item_lib);
public:
	//Constructors
	Player() = delete;
	Player(float x, float y, sf::Texture& texture, std::shared_ptr<PhysicsDevice> p_Device);
	virtual ~Player();

	//Accessors
	const std::shared_ptr<Item> getActiveRune();


	//Functions
	void updateBulletCollision(const float& dt, std::shared_ptr<TileMap> map);
	//void updateAnimation(const float& dt, const sf::Vector2f mousePosView);
	virtual void update(const float& dt, const sf::Vector2f mousePosView);
	virtual void render(sf::RenderTarget& target, sf::Shader* shader = NULL, sf::Vector2f light_position = sf::Vector2f(),  const bool show_hitbox = false);
	

	const bool getAttack();
	void setAttack(bool attacking);
private:
	sf::Shader bullet_shader;
	//variables
	bool attacking; //used internally
	bool attack; //used externally
	ItemComp* itemComp;
};

