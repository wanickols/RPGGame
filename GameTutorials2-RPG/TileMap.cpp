#include "stdafx.h"
#include "Tile.h"
#include "Entity.h"
#include "TileMap.h"

void TileMap::initTileMap()
{
	
	
}

TileMap::TileMap(float grid_size, int width, int height, std::string texture_file)
	: textureFile(texture_file), fromX(0), toX(0), fromY(0), toY(0), layer()
{
	this->gridSizeF = grid_size;
	this->gridSizeI = (int)gridSizeF;
	this->layers = 1;
	this->maxSize = { width, height };
	this->maxSizeWorldF.x = static_cast<float>(width) * gridSizeF;
	this->maxSizeWorldF.y = static_cast<float>(height) * gridSizeF;
	this->maxSizeWorldI.x = width * gridSizeI;
	this->maxSizeWorldI.y = height * gridSizeI;


	this->map.reserve(this->maxSize.x);
	for (unsigned short x = 0; x < this->maxSize.x; x++)
	{
		this->map.emplace_back(std::vector<std::vector<std::vector<std::shared_ptr<Tile>>>>());
		this->map[x].reserve(this->maxSize.y);
		for (unsigned short y = 0; y < this->maxSize.y; y++)
		{
			this->map[x].emplace_back(std::vector<std::vector<std::shared_ptr<Tile>>>());
			this->map[x][y].reserve(this->layers);
			for (unsigned short z = 0; z < this->layers; z++)
			{
				this->map[x][y].emplace_back(std::vector<std::shared_ptr<Tile>>());
				this->map[x][y][z].reserve(this->map[x][y][z].size());
				for (size_t k = 0; k < this->map[x][y][z].size(); k++) {
					this->map[x][y][z].emplace_back(nullptr);
				}
			}
		}
	}

	
	if (!this->tileSheet.loadFromFile(texture_file))
		std::cout << "ERROR::TILEMAP::FAILED TO LOAD TILETEXTURESHEET " << '\n';

	this->collisionBox.setSize(sf::Vector2f(gridSizeF, gridSizeF));
	this->collisionBox.setFillColor(sf::Color::Transparent);
	this->collisionBox.setOutlineColor(sf::Color::Red);
	this->collisionBox.setOutlineThickness(1.f);


}

TileMap::~TileMap()
{
}

//Accessors
const int TileMap::getLayerSize(const int x, const int y, const int layer) const
{
	if (x >= 0 && x < static_cast<int>(this->map.size()))
	{
		if (y >= 0 && y < static_cast<int>(this->map[x].size()))
		{
			if (layer >= 0 && layer < static_cast<int>(this->map[x][y].size()))
			{
				return this->map[x][y][layer].size();
			}
		}
	}

	return -1;
}

const sf::Texture* TileMap::getTileSheet() const
{
	return &tileSheet;
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
				for (size_t k = 0; k < this->map[x][y][z].size(); k++) {
					if (!this->map[x][y][z][k] == NULL) //sees if tile there to remove
					{
						this->map[x][y][z][k].reset();
					}
				}
			}
		}
	}
}

void TileMap::addTile(const int x, const int y, const int z, const sf::IntRect& texture_rect, const bool collision, const short type)
{
	//Take two indicies and checks to see if in array size.
	if (x >= 0 && x < this->maxSize.x && //x
		y >= 0 && y < this->maxSize.y && //y
		z >= 0 && z < this->layers)//z 
	{
		
			this->map[x][y][z].push_back(std::make_shared<Tile>(x * gridSizeF, y * gridSizeF, gridSizeF, this->tileSheet, texture_rect, collision, type));
	
	}
}

void TileMap::removeTile(const int x, const int y, const int z)
{
	//Take two indicies and checks to see if in array size.
	if (x >= 0 && x < this->maxSize.x && //x
		y >= 0 && y < this->maxSize.y && //y
		z >= 0 && z < this->layers)//z 
	{
		if (!this->map[x][y][z].empty()) //sees if tile there to remove
		{
			for (size_t k = 0; k < this->map[x][y][z].size(); k++)
				this->map[x][y][z].pop_back();
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
			<< this->gridSizeI << "\n"
			<< this->layers << "\n"
			<< this->textureFile << "\n";
		for (unsigned short x = 0; x < this->maxSize.x; x++)
		{
			for (unsigned short y = 0; y < this->maxSize.y; y++)
			{
				for (unsigned short z = 0; z < this->layers; z++)
				{
					for (size_t k = 0; k < this->map[x][y][z].size(); k++) {
						if (!this->map[x][y][z].empty()) {
							if (map[x][y][z][k] != NULL) {
								of << x << " " << y << " " << z << " ";
								of << *this->map[x][y][z][k] << " ";
							}
						}
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
	if (is.is_open())
	{
		//Map
		is >> this->maxSize.x >> this->maxSize.y
			>> this->gridSizeI
			>> this->layers
			>> this->textureFile;


		//Tile
		int x;
		int y;
		int z;
		int trX;
		int trY;
		bool collision;
		short type;


		while (is >> x >> y >> z >> trX >> trY >> collision >> type)
		{
			sf::IntRect texture_rect;
			texture_rect.left = trX; texture_rect.top = trY;
			texture_rect.width = (int)gridSizeF; texture_rect.height = (int)gridSizeF;
			
				
					//std::cout << x << y << z << trX << trY << collision << type;
				this->map[x][y][z].push_back(std::make_shared<Tile>(x * gridSizeF, y * gridSizeF, gridSizeF, this->tileSheet, texture_rect, collision, type));
		}
	}
	else
	{
		std::cout << "TILEMAP LOAD COULD OPEN TILEMAP FILE: " << file_name << "\n";
	}
	is.close();
}

void TileMap::updateCollision(std::shared_ptr<Entity> entity, const float& dt)
{
	//WORLD BOUNDS
	if (entity->getPosition().x < 0.f)
	{
		entity->setPosition(0.f, entity->getPosition().y);
		entity->stopVelocityX();
	}
	else if (entity->getPosition().x + entity->getGlobalBounds().width > this->maxSizeWorldI.x)
	{
		entity->setPosition(this->maxSizeWorldI.x - entity->getGlobalBounds().width, entity->getPosition().y);
		entity->stopVelocityX();
	}
	if (entity->getPosition().y < 0.f)
	{
		entity->setPosition(entity->getPosition().x, 0.f);
		entity->stopVelocityY();
	}
	else if (entity->getPosition().y + entity->getGlobalBounds().height > this->maxSizeWorldI.y)
	{
		entity->setPosition(entity->getPosition().x, this->maxSizeWorldI.y - entity->getGlobalBounds().height);
		entity->stopVelocityY();
	}
	
	this->layer = 0;
	this->fromX = entity->getGridPosition(this->gridSizeI).x - 5;
	if (this->fromX < 0)
		this->fromX = 0;
	else if (this->fromX > this->maxSizeWorldI.x)
		this->fromX = this->maxSizeWorldI.x;

	this->toX = entity->getGridPosition(this->gridSizeI).x + 6;
	if (this->toX < 0)
		this->toX = 0;
	else if (this->toX > this->maxSizeWorldI.x)
		this->toX = this->maxSizeWorldI.x;

	this->fromY = entity->getGridPosition(this->gridSizeI).y - 3;
	if (this->fromY < 0)
		this->fromY = 0;
	else if (this->fromY > this->maxSizeWorldI.y)
		this->fromY = this->maxSizeWorldI.y;

	this->toY = entity->getGridPosition(this->gridSizeI).y + 4;
	if (this->toY < 0)
		this->toY = 0;
	else if (this->toY > this->maxSizeWorldI.y)
		this->toY = this->maxSizeWorldI.y;
	for (int x = this->fromX; x < this->toX; x++)
	{
		for (int y = this->fromY; y < this->toY; y++)
		{
			for (size_t k = 0; k < this->map[x][y][this->layer].size(); k++) {
				if (map[x][y][this->layer][k] != nullptr) {
					sf::FloatRect playerBounds = entity->getGlobalBounds();
					sf::FloatRect wallBounds = this->map[x][y][this->layer][k]->getGlobalBounds();
					sf::FloatRect nextPositionBounds = entity->getNextPositionBounds(dt);
					if (this->map[x][y][this->layer][k]->collision &&
						this->map[x][y][this->layer][k]->intersects(nextPositionBounds)
						)
					{
						//Bottom collision
						if (playerBounds.top < wallBounds.top
							&& playerBounds.top + playerBounds.height < wallBounds.top + wallBounds.height
							&& playerBounds.left < wallBounds.left + wallBounds.width
							&& playerBounds.left + playerBounds.width > wallBounds.left
							)
						{
							entity->stopVelocityY();
							entity->setPosition(playerBounds.left, wallBounds.top - playerBounds.height);
						}

						//Top collision
						else if (playerBounds.top > wallBounds.top
							&& playerBounds.top + playerBounds.height > wallBounds.top + wallBounds.height
							&& playerBounds.left < wallBounds.left + wallBounds.width
							&& playerBounds.left + playerBounds.width > wallBounds.left
							)
						{
							entity->stopVelocityY();
							entity->setPosition(playerBounds.left, wallBounds.top + wallBounds.height);
						}

						//Right collision
						if (playerBounds.left < wallBounds.left
							&& playerBounds.left + playerBounds.width < wallBounds.left + wallBounds.width
							&& playerBounds.top < wallBounds.top + wallBounds.height - 1.f
							&& playerBounds.top + playerBounds.height > wallBounds.top + 1.f
							)
						{
							entity->stopVelocityX();
							entity->setPosition(wallBounds.left - playerBounds.width, playerBounds.top);
						}

						//Left collision
						else if (playerBounds.left > wallBounds.left
							&& playerBounds.left + playerBounds.width > wallBounds.left + wallBounds.width
							&& playerBounds.top < wallBounds.top + wallBounds.height - 1.f
							&& playerBounds.top + playerBounds.height > wallBounds.top + 1.f
							)
						{
							entity->stopVelocityX();
							entity->setPosition(wallBounds.left + wallBounds.width, playerBounds.top);
						}
					}
				}
			}
		}

	}
}


void TileMap::update()
{
}

void TileMap::render(sf::RenderTarget& target, const sf::Vector2i& gridPosition)
{
		this->layer = 0;

		this->fromX = gridPosition.x - 5;
		if (this->fromX < 0)
			this->fromX = 0;
		else if (this->fromX > this->maxSizeWorldI.x)
			this->fromX = this->maxSizeWorldI.x;

		this->toX = gridPosition.x + 6;
		if (this->toX < 0)
			this->toX = 0;
		else if (this->toX > this->maxSizeWorldI.x)
			this->toX = this->maxSizeWorldI.x;

		this->fromY = gridPosition.y - 5;
		if (this->fromY < 0)
			this->fromY = 0;
		else if (this->fromY > this->maxSizeWorldI.y)
			this->fromY = this->maxSizeWorldI.y;

		this->toY = gridPosition.y + 6;
		if (this->toY < 0)
			this->toY = 0;
		else if (this->toY > this->maxSizeWorldI.y)
			this->toY = this->maxSizeWorldI.y;

		for (int x = this->fromX; x < this->toX; x++)
		{
			for (int y = this->fromY; y < this->toY; y++)
			{
				for (size_t k = 0; k < this->map[x][y][this->layer].size(); k++) {
					if(this->map[x][y][this->layer][k]->getType() == TileType::DEFERRED)
					{
						this->deferredRenderStack.push(this->map[x][y][this->layer][k]);
					}
					else {
						if (map[x][y][this->layer][k] != NULL) {
							this->map[x][y][this->layer][k]->render(target);
						}
					}

					if (this->map[x][y][this->layer][k]->getCollision()) {
						this->collisionBox.setPosition(map[x][y][this->layer][k]->getPosition());
						target.draw(this->collisionBox);
					}
				}
			}

		}
}


void TileMap::renderDeferred(sf::RenderTarget& target)
{
	while (!this->deferredRenderStack.empty())
	{
		deferredRenderStack.top()->render(target);

		deferredRenderStack.pop();
	}
}




