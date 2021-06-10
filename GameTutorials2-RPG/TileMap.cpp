#include "stdafx.h"
#include "Tile.h"
#include "Entity.h"
#include "TileMap.h"

TileMap::TileMap(float grid_size, unsigned width, unsigned height, std::string texture_file)
	: textureFile(texture_file)
{
	this->gridSizeF = grid_size;
	this->gridSizeU = (unsigned)gridSizeF;
	this->layers = 1;
	this->maxSize = { width, height };
	this->maxSizeWorldF.x = static_cast<float>(width) * gridSizeF;
	this->maxSizeWorldF.y = static_cast<float>(height) * gridSizeF;


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

	this->collisionBox.setSize(sf::Vector2f(gridSizeF, gridSizeF));
	this->collisionBox.setFillColor(sf::Color::Transparent);
	this->collisionBox.setOutlineColor(sf::Color::Red);
	this->collisionBox.setOutlineThickness(1.f);

	this->maxSizeWorldF.x = width * gridSizeF;
	this->maxSizeWorldF.y = height * gridSizeF;
}

TileMap::~TileMap()
{
}

//Functions
void TileMap::clear()
{
	for (unsigned short x = 0; x < this->maxSize.x; x++)
	{
		for (unsigned short y = 0; y < this->maxSize.y; y++)
		{
			for (unsigned short z = 0; z < this->layers; z++)
			{
				if (!this->map[x][y][z] == NULL) //sees if tile there to remove
				{
					this->map[x][y][z].reset();
				}
			}
		}
	}
}

void TileMap::addTile(const unsigned x, const unsigned y, const unsigned z, const sf::IntRect& texture_rect, const bool collision, const short type)
{
	//Take two indicies and checks to see if in array size.
	if (x >= 0 && x < this->maxSize.x && //x
		y >= 0 && y < this->maxSize.y && //y
		z >= 0 && z < this->layers)//z 
	{
		if (this->map[x][y][z] == NULL) //sees if tile is empty
		{
			this->map[x][y][z] = std::make_unique<Tile>(x * gridSizeF, y * gridSizeF, gridSizeF, this->tileSheet, texture_rect, collision, type);
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
	gridPos x y layer, Texture rect x y, type, collision
	*/

	std::ofstream of;
	of.open(file_name);

	if (of.is_open())
	{
		of << this->maxSize.x << " " << this->maxSize.y << "\n"
			<< this->gridSizeU << "\n"
			<< this->layers << "\n"
			<< this->textureFile << "\n";
		for (unsigned short x = 0; x < this->maxSize.x; x++)
		{
			for (unsigned short y = 0; y < this->maxSize.y; y++)
			{
				for (unsigned short z = 0; z < this->layers; z++)
				{
					if (this->map[x][y][z] != NULL) {
						of << x << " " << y << " " << z << " ";
						of << *this->map[x][y][z] << " ";
					}
				}

			}

		}

	}
	else
	{
		std::cout << "TILEMAP SAVE COULD OPEN TILEMAP FILE: " << file_name << "\n";
	}
	of.close();


}

void TileMap::loadFromFile(const std::string file_name)
{
	this->clear();
	std::ifstream is;
	is.open(file_name);

	//Map
	is >> this->maxSize.x >> this->maxSize.y
		>> this->gridSizeU
		>> this->layers
		>> this->textureFile;

	//Tile
	unsigned x;
	unsigned y;
	unsigned z;
	unsigned int trX;
	unsigned int trY;
	bool collision;
	short type;

	if (is.is_open())
	{
		while (is >> x >> y >> z >> trX >> trY >> collision >> type)
		{
			if (map[x][y][z] != NULL)
				map[x][y][z] = NULL;

			sf::IntRect texture_rect;
			texture_rect.left = trX; texture_rect.top = trY;
			texture_rect.width = (int)gridSizeF; texture_rect.height = (int)gridSizeF;
			this->map[x][y][z] = std::make_unique<Tile>(x * gridSizeF, y * gridSizeF, gridSizeF, this->tileSheet, texture_rect, collision, type);

		}


	}
	else
	{
		std::cout << "TILEMAP LOAD COULD OPEN TILEMAP FILE: " << file_name << "\n";
	}
	is.close();
}

void TileMap::updateCollision(std::shared_ptr<Entity> entity)
{
	//WORLD BOUNDS
	if (entity->getPosition().x < 0.f)
	{
		entity->setPosition(0.f, entity->getPosition().y);
		entity->stopVelocityX();
	}
	else if (entity->getPosition().x + entity->getGlobalBounds().width > this->maxSizeWorldF.x)
	{
		entity->setPosition(this->maxSizeWorldF.x - entity->getGlobalBounds().width, entity->getPosition().y);
		entity->stopVelocityX();
	}
	if (entity->getPosition().y < 0.f)
	{
		entity->setPosition(entity->getPosition().x, 0.f);
		entity->stopVelocityY();
	}
	else if (entity->getPosition().y + entity->getGlobalBounds().height > this->maxSizeWorldF.y)
	{
		entity->setPosition(entity->getPosition().x, this->maxSizeWorldF.y - entity->getGlobalBounds().height);
		entity->stopVelocityY();
	}
}


void TileMap::update()
{
}

void TileMap::render(sf::RenderTarget& target, std::unique_ptr<Entity> entity)
{
	for (auto& x : this->map) {
		for (auto& y : x)
		{
			for (auto& z : y)
			{

				if (z != nullptr) {
					z->render(target);
					if (z->collision) {
						this->collisionBox.setPosition(z->getPosition());
						target.draw(this->collisionBox);
					}

				}
			}
		}
	}
}

const sf::Texture* TileMap::getTileSheet() const
{
	return &tileSheet;
}

