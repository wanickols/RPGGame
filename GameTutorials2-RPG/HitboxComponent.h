#pragma once

class sf::RenderTarget;
class sf::Sprite;

class HitboxComponent
{
public:
	HitboxComponent(sf::Sprite& sprite, float offset_x, float offset_y, float width, float height);
	virtual ~HitboxComponent();

	//Accessors
	const sf::FloatRect getGlobalBounds() const;
	const sf::Vector2f& getPosition() const; 
	const sf::FloatRect getNextPosition(const sf::Vector2f& velocity);

	//Modifiers
	void setPosition(const sf::Vector2f& position);

	//functions
	bool intersect(const sf::FloatRect& frect);

	void update();
	void render(sf::RenderTarget& target);
private:
	sf::Sprite& sprite;
	sf::RectangleShape hitbox;
	sf::FloatRect nextPosition;
	float offSetX;
	float offSetY;
};

