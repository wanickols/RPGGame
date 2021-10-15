#pragma once
#include "Entity.h"

class EnemySpawner;
class Item;
enum EnemyType { RAT = 0, BIRD = 1, WORM = 2};

class Enemy : public Entity
{
private:
	virtual void initVariables() {};
	virtual void initComponents() {};
	virtual void initAnimations(sf::Texture& texture_sheet, float x, float y) = 0;
public:

	Enemy();
	~Enemy();
	virtual void updateAnimation(const float& dt) = 0;
	virtual void update(const float& dt, const sf::Vector2f mousePosView = sf::Vector2f(0.f, 0.f)) = 0;
	virtual void render(sf::RenderTarget& target, sf::Shader* shader = NULL, sf::Vector2f light_position = sf::Vector2f(), const bool show_hitbox = false) = 0;

protected:

	//For Player
	
};

