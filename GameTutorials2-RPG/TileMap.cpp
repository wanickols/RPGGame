#include "stdafx.h"
#include "Tile.h"
#include "TileMap.h"

TileMap::TileMap(float grid_size, unsigned width, unsigned height, std::string texture_file)
	: textureFile(texture_file)
{
	this->gridSizeF = grid_size;
	this->gridSizeU = (unsigned)gridSizeF;
	this->layers = 1;
	this->maxSize = { width, height };

	this->map.reserve(this->maxSize.x);

	for (unsigned short x = 0; x < this->maxSize.x; x++)
	{
		this->map.emplace_back(std::vector<std::vector<std::unique_ptr<Tile>>>());
		this->map[x].reserve(this->maxSize.y);
		for (unsigned short y = 0; y < this->maxSize.y; y++)
		{
			this->map[x].emplace_back(std::vector<std::unique_ptr<Tile>>());
			this->map[x][y].reserve(this->layers);
			for (unsigned short z = 0; z < this->layers; z++)
			{
				this->map[x][y].emplace_back(nullptr);
			}

		}

	}
	if (!this->tileSheet.loadFromFile(texture_file))
		std::cout << "ERROR::TILEMAP::FAILED TO LOAD TILETEXTURESHEET " << '\n';
}

TileMap::~TileMap()
{
}

//Functions
void TileMap::addTile(const unsigned x, const unsigned y, const unsigned z, const sf::IntRect& texture_rect)
{
	//Take two indicies and checks to see if in array size.
	if (x >= 0 && x < this->maxSize.x && //x
		y >= 0 && y < this->maxSize.y && //y
		z >= 0 && z < this->layers)//z 
	{
		if (this->map[x][y][z] == NULL) //sees if tile is empty
		{
			this->map[x][y][z] = std::make_unique<Tile>(x * gridSizeF, y * gridSizeF, gridSizeF, this->tileSheet, texture_rect);
		}
	}
}

void TileMap::removeTile(const unsigned x, const unsigned y, const unsigned z)
{
	//Take two indicies and checks to see if in array size.
	if (x >= 0 && x < this->maxSize.x && //x
		y >= 0 && y < this->maxSize.y && //y
		z >= 0 && z < this->layers)//z 
	{
		if (!this->map[x][y][z] == NULL) //sees if tile there to remove
		{
			this->map[x][y][z].reset();

		}
	}
}

void TileMap::saveToFile(const std::string file_name)
{
	/*Saves the tilemape to a text file
	Format:
	Basic:
	Size x y
	gridSize
	layers
	texture file

	All tiles
	gridPos x y, Texture rect x y
	*/

	std::ofstream of;
	of.open(file_name);

	if (of.is_open())
	{
		of << this->maxSize.x << " " << this->maxSize.y << "\n"
		   << this->gridSizeU << "\n"
		   << this->textureFile << "\n";
		for (unsigned short x = 0; x < this->maxSize.x; x++)
		{
			for (unsigned short y = 0; y < this->maxSize.y; y++)
			{
				for (unsigned short z = 0; z < this->layers; z++)
				{
					if(this->map[x][y][z] != NULL)
					of << *this->map[x][y][z];
				}

			}

		}

	}
	else
	{
		std::cout << "TILEMAP COULD OPEN TILEMAP FILE: " << file_name << "\n";
	}
	of.close();


}

void TileMap::loadFromFile(const std::string file_name)
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
				if(z != nullptr)
				z->render(target);
			}
		}
	}
}

const sf::Texture* TileMap::getTileSheet() const
{
	return &tileSheet;
}

