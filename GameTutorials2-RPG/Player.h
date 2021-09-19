#pragma once
#include "Entity.h"
#include "Queue"
#include "Bullet.h"

class TileMap;

class Player :
	public Entity
{
private:
	//Init Functions
	void initVariables();
	void initComponents();
public:
	//Constructors
	Player() = delete;
	Player(float x, float y, sf::Texture& texture);
	virtual ~Player();

	//Accessors
	std::shared_ptr<AttributeComponent> getAttributeComponent();

	//Functions
	void loseHealth(const int health);
	void addHealth(const int health);
	void loseEnergy(const int energy);
	void addEnergy(const int energy);
	void loseExp(const int exp);
	void addExp(const int exp);
	void shoot(const sf::Vector2f& mousePosView);
	
	void updateBulletCollision(const float& dt, std::shared_ptr<TileMap> map);
	void updateAnimation(const float& dt, const sf::Vector2f& mousePosView);
	virtual void update(const float& dt, const sf::Vector2f& mousePosView);
	virtual void render(sf::RenderTarget& target, sf::Shader* shader = NULL, const bool show_hitbox = false);
private:

	//variables
	std::vector <std::shared_ptr<Bullet> > bullets;
	sf::Texture bulletTexture;
	bool attacking;
};

