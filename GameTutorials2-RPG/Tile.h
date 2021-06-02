#pragma once

class Tile
{
public:
	Tile(float x, float y, float gridSizeF);

	//Functions
	void update();
	void render(sf::RenderTarget& target);
protected:
	sf::RectangleShape shape;
};

