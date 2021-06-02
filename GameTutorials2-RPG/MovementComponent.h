#pragma once

enum movement_states { IDLE = 0, ATTACK, MOVING_LEFT, MOVING_RIGHT, MOVING_UP, MOVING_DOWN };

class MovementComponent
{
private:
	//Initializer functions

public:
	MovementComponent(sf::Sprite& sprite, float maxVelocity, float acceleration, float deceleration);
	virtual ~MovementComponent();
	
	//Accessors
	const sf::Vector2f& getVelocity();
	const float& getMaxVelocity() const;
	const bool getState(const short unsigned state) const;

	//functions
	void move(const float x, const float y, const float& dt);
	void update(const float& dt);
private:
	sf::Sprite& sprite;

	float maxVelocity;
	float acceleration;
	float deceleration;

	sf::Vector2f velocity;

};

