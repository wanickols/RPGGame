#pragma once

enum TileType { DEFAULT = 0, DAMAGING, DEFERRED, ENEMYSPAWNER };

class ofstream;
class Tile
{
public:
	Tile(float x, float y, const sf::Texture& texture, const sf::IntRect& texture_rect, bool collison = false, short type = TileType::DEFAULT);
	bool collision;
	short type = 0;


	//Accessors
	const short& getType() const;
	const bool getCollision() const;
	const sf::Vector2f& getPosition() const;
	const sf::FloatRect getGlobalBounds() const;

	//Functions
	virtual std::ofstream& getStringTile(std::ofstream& os);
	friend std::ofstream& operator<<(std::ofstream& os, Tile& tile);

	const bool intersects(const sf::FloatRect bounds) const;
	virtual void update(const float& dt);
	void render(sf::RenderTarget& target, const sf::Vector2f playerPosition = sf::Vector2f(), sf::Shader* shader = NULL);
	sf::Sprite shape;
};

