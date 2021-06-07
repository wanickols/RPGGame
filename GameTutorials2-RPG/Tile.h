#pragma once

enum TileType {DEFAULT = 0, DAMAGING};

class ofstream;
class Tile
{
public:
	Tile(float x, float y, float gridSizeF, const sf::Texture& texture, const sf::IntRect& texture_rect);
	bool collision;
	short type;

	//Functions
	friend std::ofstream& operator<<(std::ofstream& os, Tile& tile);

	void update();
	void render(sf::RenderTarget& target);
protected:
	sf::RectangleShape shape;
};

