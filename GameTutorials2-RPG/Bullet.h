#pragma once
#include "Entity.h"

class Bullet : public Entity
{
public:
	Bullet() = delete;
	Bullet(float x, float y, float velX, float velY, sf::Texture& texture, const unsigned short state);
	void updateAnimation(const float& dt);
	virtual void update(const float& dt, const sf::Vector2f mousePosView = sf::Vector2f(0.f,0.f));
	virtual void render(sf::RenderTarget& target, sf::Shader* shader = NULL, sf::Vector2f light_position = sf::Vector2f(), const bool show_hitbox = false);
	const bool getRunning() const;

private:
	bool running;
	float xVel;
	float yVel;
};

