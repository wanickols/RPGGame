#pragma once
#include "Entity.h"

class Bullet : public Entity
{
public:
	Bullet() = delete;
	Bullet(float x, float y, float velX, float velY, sf::Texture& texture, const unsigned short state);
	void updateAnimation(const float& dt);
	virtual void update(const float& dt);
	virtual void render(sf::RenderTarget& target, sf::Shader* shader = NULL, const bool show_hitbox = false);
	const bool getRunning() const;

private:
	bool running;
	float xVel;
	float yVel;
};

