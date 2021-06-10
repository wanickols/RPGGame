#pragma once
#include "Entity.h"

namespace sf {
	class Texture;
	class RenderTarget;
	class RectangleShape;
}

class Tile;

class TileMap
{
public:
	
	TileMap(float grid_size, unsigned width, unsigned height, std::string texture_file);
	virtual ~TileMap();
	
	//Functions
	void clear();
	void addTile(const unsigned x, const unsigned y, const unsigned z, const sf::IntRect& texture_rect, const bool collision, const short type);
	void removeTile(const unsigned x, const unsigned y, const unsigned z);
	void saveToFile(const std::string file_name);
	void loadFromFile(const std::string file_name);

	void updateCollision(std::shared_ptr<Entity> entity);
	
	void update();
	void render(sf::RenderTarget& Target, std::unique_ptr<Entity> entity = NULL);

	//Accessors 
	const sf::Texture* getTileSheet() const;


private:
	sf::Vector2u maxSize;
	sf::Vector2f maxSizeWorldF;
	std::string textureFile;
	unsigned layers;
	float gridSizeF;
	unsigned gridSizeU;
	sf::Texture tileSheet;
	sf::RectangleShape collisionBox;
	//   x            y				z(depth)
	std::vector< std::vector< std::vector<std::unique_ptr<Tile>> > > map;
	
};


