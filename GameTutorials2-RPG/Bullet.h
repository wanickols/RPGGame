#pragma once
#include "Entity.h"
#include "Movement.h"

class Bullet : public Entity
{
public:
	Bullet() = delete;
	Bullet(float x, float y, float velX, float velY, sf::Texture& texture, const facing direction, std::shared_ptr<PhysicsDevice> p_device);
	virtual void update(const float& dt, const sf::Vector2f mousePosView = sf::Vector2f(0.f,0.f));
	virtual void render(sf::RenderTarget& target, sf::Shader* shader = NULL, sf::Vector2f light_position = sf::Vector2f(), const bool show_hitbox = false);
private:

};

