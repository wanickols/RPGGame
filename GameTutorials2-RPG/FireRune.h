#pragma once
#include "Rune.h"
class Bullet;

class FireRune : public Rune
{
public:
	FireRune();
	

	//Functions
	void shoot(float playerX, float playerY, float playerVelX, float playerVelY, const unsigned short lastStates);
	void update(const float& dt, const sf::Vector2f& mousePosView);
	void render(sf::RenderTarget& target, sf::Shader* shader = NULL, const bool show_hitbox = false);
	
private:

};

