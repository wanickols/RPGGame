#pragma once
#include "Entity.h"

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

	//Functions
	void updateAnimation(const float& dt);
	virtual void update(const float& dt);
	virtual void render(sf::RenderTarget& target);
private:

	//variables
	bool attacking;
};

