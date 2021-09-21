#pragma once
#include "Item.h"

class Bullet;
class TileMap;

class Rune : public Item
{
public:
	Rune() {};

	void updateBulletCollision(const float& dt, std::shared_ptr<TileMap> map);
	virtual void update(const float& dt, const sf::Vector2f& mousePosView) = 0;
	virtual void render(sf::RenderTarget& target, sf::Shader* shader = NULL, const bool show_hitbox = false) = 0;
	virtual void shoot(float playerX, float playerY, float playerVelX, float playerVelY, const unsigned short lastState) = 0; \

	//accessors
	const bool isBulletEmpty();
protected:
	std::vector <std::shared_ptr<Bullet> > bullets;
	sf::Texture bulletTexture;
private:
	
};

