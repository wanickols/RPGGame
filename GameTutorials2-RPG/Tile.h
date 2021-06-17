#pragma once

enum TileType { DEFAULT = 0, DAMAGING, DEFERRED };

class ofstream;
class Tile
{
public:
	Tile(float x, float y, float gridSizeF, const sf::Texture& texture, const sf::IntRect& texture_rect, bool collison = false, short type = TileType::DEFAULT);
	bool collision;
	short type = 0;


	//Accessors
	const short& getType() const;
	const bool getCollision() const;
	const sf::Vector2f& getPosition() const;
	const sf::FloatRect getGlobalBounds() const;

	//Functions
	friend std::ofstream& operator<<(std::ofstream& os, Tile& tile);

	const bool intersects(const sf::FloatRect bounds) const;
	void update();
	void render(sf::RenderTarget& target);
protected:
	sf::RectangleShape shape;
};

