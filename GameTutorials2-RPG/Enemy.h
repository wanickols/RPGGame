#pragma once
#include "Entity.h"

class EnemySpawner;
class Item;

class Enemy : public Entity
{
private:
	void initVariables();
	void initComponents();
	void initAnimations(sf::Texture& texture_sheet);
public:

	Enemy(float x, float y, sf::Texture& texture, EnemySpawner& origin);
	~Enemy();
	void updateAnimation(const float& dt, const sf::Vector2f& mousePosView);
	virtual void update(const float& dt, const sf::Vector2f& mousePosView);
	virtual void render(sf::RenderTarget& target, sf::Shader* shader = NULL, const bool show_hitbox = false);

private:

	//For Player
	std::unique_ptr<EnemySpawner> Origin;
	std::unique_ptr<Item> dropItem; //Item Dropped when enemy dies;
	int expWorth; //Exp given when enemy dies
};

