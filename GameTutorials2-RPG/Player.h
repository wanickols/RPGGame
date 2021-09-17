#pragma once
#include "Entity.h"
#include "Queue"
#include "Bullet.h"

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
	void shoot();

	void updateAnimation(const float& dt);
	virtual void update(const float& dt);
	virtual void render(sf::RenderTarget& target, sf::Shader* shader = NULL, const bool show_hitbox = false);
private:

	//variables
	std::vector <std::unique_ptr<Bullet> > bullets;
	sf::Texture bulletTexture;
	bool attacking;
};

