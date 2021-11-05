#pragma once
#include "Component.h"

class sf::RenderTarget;
class sf::Sprite;
class Entity;

class Hitbox : public Component
{
public:
	Hitbox(sf::Sprite& sprite, float offset_x, float offset_y, float width, float height, Entity& owner);
	virtual ~Hitbox();

	//Accessors
	const sf::FloatRect getGlobalBounds() const;
	const sf::Vector2f& getPosition() const; 
	const sf::FloatRect& getNextPosition(const sf::Vector2f& velocity);

	//Modifiers
	void setPosition(const sf::Vector2f& position);
	void setNextPosition(const sf::Vector2f& position);

	//functions
	bool intersect(const sf::FloatRect& frect);

	void update(const float& dt, const sf::Vector2f mousePosView);
	void render(sf::RenderTarget& target, sf::Shader* shader, sf::Vector2f light_position, const bool show_hitbox);
private:
	sf::Sprite& sprite;
	sf::RectangleShape hitbox;
	sf::FloatRect nextPosition;
	float offSetX;
	float offSetY;
};

