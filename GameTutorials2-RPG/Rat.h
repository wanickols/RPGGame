#pragma once
#include "Enemy.h"

class Rat : public Enemy
{
private:
	void initVariables();
	void initComponents();
	void initAnimations(sf::Texture& texture_sheet);
public:
	
	Rat(float x, float y, sf::Texture& texture, EnemySpawner& origin);
	
	void updateAnimation(const float& dt);
	void update(const float& dt, const sf::Vector2f mousePosView = sf::Vector2f(0.f, 0.f));
	void render(sf::RenderTarget& target, sf::Shader* shader = NULL, sf::Vector2f light_position = sf::Vector2f(), const bool show_hitbox = false);

private:

};

