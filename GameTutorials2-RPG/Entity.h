#pragma once
#include "HitboxComponent.h"
#include "MovementComponent.h"
#include "AnimationComponent.h"

class Entity
{
private:
	void initVariables();

public:
	Entity();
	virtual ~Entity();

	//component functions
	void setTexture(sf::Texture& texture);
	void createMovementComponent(const float maxVelocity, const float acceleration, const float deceleration);
	void createAnimationComponent(sf::Texture& texture_sheet);
	void createHitBoxComponent(sf::Sprite& sprite, const float offset_x, const float offset_y, float width, float height);
	
	virtual void setPosition(float x, float y);

	//functions
	virtual void move(const float x, const float y, const float& dt);

	virtual void update(const float& dt);
	virtual void render(sf::RenderTarget& target);
protected:

	std::unique_ptr<HitboxComponent> hitBoxComponent;
	std::unique_ptr<MovementComponent> movementComponent;
	std::unique_ptr<AnimationComponent> animationComponent;
	sf::Sprite sprite;


};

