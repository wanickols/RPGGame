#pragma once

class Tile;

class TileMap
{
public:
	
	TileMap(float grid_size, unsigned width, unsigned height, std::string texture_file);
	virtual ~TileMap();
	
	//Functions
	void addTile(const unsigned x, const unsigned y, const unsigned z, const sf::IntRect& texture_rect);
	void removeTile(const unsigned x, const unsigned y, const unsigned z);
	void saveToFile(const std::string file_name);
	void loadFromFile(const std::string file_name);


	
	void update();
	void render(sf::RenderTarget& Target);

	//Accessors 
	const sf::Texture* getTileSheet() const;


private:
	sf::Vector2u maxSize;
	std::string textureFile;
	unsigned layers;
	float gridSizeF;
	unsigned gridSizeU;
	sf::Texture tileSheet;
	//   x            y				z(depth)
	std::vector< std::vector< std::vector<std::unique_ptr<Tile>> > > map;
	
};


