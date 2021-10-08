#pragma once
#include "Entity.h"

class EnemySpawner;
class Item;

class Enemy : public Entity
{
private:
	virtual void initVariables();
	void initComponents();
	void initAnimations(sf::Texture& texture_sheet);
public:

	Enemy(float x, float y, sf::Texture& texture, EnemySpawner& origin);
	~Enemy();
	virtual void updateAnimation(const float& dt);
	virtual void update(const float& dt, const sf::Vector2f mousePosView = sf::Vector2f(0.f, 0.f));
	virtual void render(sf::RenderTarget& target, sf::Shader* shader = NULL, sf::Vector2f light_position = sf::Vector2f(), const bool show_hitbox = false);

protected:

	//For Player
	std::unique_ptr<EnemySpawner> Origin;
	std::unique_ptr<Item> dropItem; //Item Dropped when enemy dies;
	int expWorth; //Exp given when enemy dies
	std::string name;
};

