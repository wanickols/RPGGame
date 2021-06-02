#pragma once
#include "Tile.h"

class TileMap
{
public:
	
	TileMap(float grid_size, unsigned width, unsigned height);
	virtual ~TileMap();
	
	//Functions
	void update();
	void render(sf::RenderTarget& Target);
private:
	sf::Vector2u maxSize;
	unsigned layers;
	float gridSizeF;
	unsigned gridSizeU;
	//   x            y				z(depth)
	std::vector< std::vector< std::vector<Tile> > > map;
	
};


