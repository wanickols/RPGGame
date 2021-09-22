#pragma once
#include "Entity.h"
#include "Queue"
#include "Bullet.h"
#include "FireRune.h"

class TileMap;

class Player :
	public Entity
{
private:
	//Init Functions
	void initVariables();
	void initComponents();
	void initAnimations(sf::Texture& texture_sheet);
	void initRunes();
public:
	//Constructors
	Player() = delete;
	Player(float x, float y, sf::Texture& texture);
	virtual ~Player();

	//Accessors
	std::shared_ptr<AttributeComponent> getAttributeComponent();
	const facing getDirection() const;
	void setDirection(facing new_direction);

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
	virtual void render(sf::RenderTarget& target, sf::Shader* shader = NULL, sf::Vector2f light_position = sf::Vector2f(),  const bool show_hitbox = false);
private:

	std::vector< std::shared_ptr<Rune> > runes;
	std::shared_ptr <Rune> activeRune;
	//variables
	bool attacking;
};

