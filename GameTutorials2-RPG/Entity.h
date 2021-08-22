#pragma once
#include "HitboxComponent.h"
#include "MovementComponent.h"
#include "AnimationComponent.h"
#include "AttributeComponent.h"

namespace sf {
	class Texture;
	class Sprite;
	class RenderTarget;
}

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
	void creatAttributeComponent(int level);
	void createHitBoxComponent(sf::Sprite& sprite, const float offset_x, const float offset_y, float width, float height);

	const virtual sf::Vector2f getPosition() const;
	const virtual sf::Vector2i getGridPosition(const int& gridSizeI);
	const sf::FloatRect& getNextPositionBounds(const float& dt) const;
	

	const sf::FloatRect getGlobalBounds() const;

	virtual void setPosition(float x, float y);

	//functions
	virtual void move(const float x, const float y, const float& dt);
	virtual void stopVelocity();
	virtual void stopVelocityX();
	virtual void stopVelocityY();

	virtual void update(const float& dt) = 0;
	virtual void render(sf::RenderTarget& target) = 0;
protected:

	std::unique_ptr<HitboxComponent> hitBoxComponent;
	std::unique_ptr<MovementComponent> movementComponent;
	std::unique_ptr<AnimationComponent> animationComponent;
	std::shared_ptr<AttributeComponent> attributeComponent;
	sf::Sprite sprite;
private:
	sf::Vector2i gridPosition;
};

