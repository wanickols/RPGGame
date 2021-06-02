#pragma once
class HitboxComponent
{
public:
	HitboxComponent(sf::Sprite& sprite, float offset_x, float offset_y, float width, float height);
	virtual ~HitboxComponent();
	
	//functions
	bool checkCollision(const sf::FloatRect& frect);

	void update();
	void render(sf::RenderTarget& target);
private:
	sf::Sprite& sprite;
	sf::RectangleShape hitbox;
	float offSetX;
	float offSetY;
};

