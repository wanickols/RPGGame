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
	Movement(sf::Sprite& sprite, sf::Vector2f maxVelocity, sf::Vector2f acceleration, sf::Vector2f deceleration, Entity& owner);
	virtual ~Movement();

	//Accessors
	//const sf::Vector2f& getVelocity(Entity& owner);
	const sf::Vector2f& getMaxVelocity() const;
	const facing getDirection() const;
	const bool getMOVING();
	void setMOVING(const bool);
	void setDirection(facing player_direction);
	void setAcceleration(sf::Vector2f newAccel);
	void decelerate(sf::Vector2f deceleration = sf::Vector2f());
	void setAcceleration(sf::Vector2f& newAccel);
	void setAcceleration(float accelX, float accelY);

	//functions
	void stopVelocity();
	void halfVelocity();
	void stopVelocityX();
	void stopVelocityY();
	void move(const float x, const float y, const float& dt, bool bullet = false);
	void update(const float& dt, const sf::Vector2f mousePosView);
	void render(sf::RenderTarget& target, sf::Shader* shader, sf::Vector2f light_position, const bool show_hitbox);
private:
	sf::Sprite& sprite;

	sf::Vector2f maxVelocity;
	sf::Vector2f acceleration;
	sf::Vector2f velocity;
	sf::Vector2f deceleration;

	std::shared_ptr<PhysicsDevice> pDevice;

	facing direction;
	bool MOVING;


};

