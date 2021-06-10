#pragma once

enum TileType { DEFAULT = 0, DAMAGING };

class ofstream;
class Tile
{
public:
	Tile(float x, float y, float gridSizeF, const sf::Texture& texture, const sf::IntRect& texture_rect, bool collison = false, short type = TileType::DEFAULT);
	bool collision;
	short type = 0;


	//Accessors
	const sf::Vector2f& getPosition() const;

	//Functions
	friend std::ofstream& operator<<(std::ofstream& os, Tile& tile);

	void update();
	void render(sf::RenderTarget& target);
protected:
	sf::RectangleShape shape;
};

