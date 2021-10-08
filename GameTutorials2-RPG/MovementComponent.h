#pragma once


	enum movement_states { DOWNIDLE = 0, UPIDLE, LEFTIDLE, RIGHTIDLE, ATTACK, MOVING_LEFT, MOVING_RIGHT, MOVING_UP, MOVING_DOWN };
	enum class facing {DOWN, UP, LEFT, RIGHT};
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
	const bool getState(const short unsigned state);
	const unsigned short int getState();
	const unsigned short int getLastState() const;
	const facing getDirection() const;
	void setDirection(facing player_direction);
	void setLastState(const short unsigned state);
	void setAcceleration(float newAccel);

	//functions
	void stopVelocity();
	void stopVelocityX();
	void stopVelocityY();
	void move(const float x, const float y, const float& dt, bool player = false);
	void update(const float& dt);
private:
	sf::Sprite& sprite;

	float maxVelocity;
	float acceleration;
	float deceleration;

	unsigned short lastState;
	facing direction;
	sf::Vector2f velocity;

};

