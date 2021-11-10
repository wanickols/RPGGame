#pragma once
#include "Component.h"

class PhysicsDevice;

class Entity;
	enum class facing {DOWN = 0, UP, LEFT, RIGHT};
	
	class Movement : public Component
{
private:
	//Initializer functions

public:
	Movement(sf::Sprite& sprite, float maxVelocity, float acceleration, float deceleration, Entity& owner);
	virtual ~Movement();

	//Accessors
	//const sf::Vector2f& getVelocity(Entity& owner);
	const float& getMaxVelocity() const;
	const facing getDirection() const;
	const bool getMOVING();
	void setMOVING(const bool);
	void setDirection(facing player_direction);
	void setAcceleration(float newAccel);

	//functions
	void stopVelocity();
	void halfVelocity();
	void stopVelocityX();
	void stopVelocityY();
	void move(const float x, const float y, const float& dt, bool player = false);
	void update(const float& dt, const sf::Vector2f mousePosView);
	void render(sf::RenderTarget& target, sf::Shader* shader, sf::Vector2f light_position, const bool show_hitbox);
private:
	sf::Sprite& sprite;

	float maxVelocity;
	float acceleration;
	float deceleration;

	std::shared_ptr<PhysicsDevice> pDevice;

	facing direction;
	bool MOVING;
	sf::Vector2f velocity;
	

};

