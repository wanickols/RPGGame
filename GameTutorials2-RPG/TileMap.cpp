#include "stdafx.h"
#include "TileMap.h"

TileMap::TileMap(float grid_size, unsigned width, unsigned height)
{
	this->gridSizeF = grid_size;
	this->gridSizeU = (unsigned)gridSizeF;
	this->layers = 1;
	this->maxSize = { width, height };

	this->map.reserve(this->maxSize.x);

	for (unsigned short x = 0; x < this->maxSize.x; x++)
	{
		this->map.emplace_back(std::vector<std::vector<Tile> >());
		this->map[x].reserve(this->maxSize.y);
		for (unsigned short y = 0; y < this->maxSize.y; y++)
		{
			this->map[x].emplace_back(std::vector<Tile>());
			this->map[x][y].reserve(this->layers);
			for (unsigned short z = 0; z < this->layers; z++)
			{
				this->map[x][y].emplace_back(Tile(x * this->gridSizeF, y * gridSizeF, this->gridSizeF));
			}

		}

	}
}

TileMap::~TileMap()
{
}

void TileMap::update()
{
}

void TileMap::render(sf::RenderTarget& target)
{
	for (auto& x : this->map) {
		for (auto& y : x)
		{
			for (auto& z : y)
			{
				z.render(target);
			}
		}
	}
}
