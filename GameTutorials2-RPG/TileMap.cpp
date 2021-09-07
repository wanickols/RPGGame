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
	gridSizeF = grid_size;
	gridSizeI = static_cast<int>(grid_size);
	layers = 1;
	maxSize = { width, height };
	maxSizeWorldF.x = static_cast<float>(width) * gridSizeF;
	maxSizeWorldF.y = static_cast<float>(height) * gridSizeF;
	maxSizeWorldI.x = width * gridSizeI;
	maxSizeWorldI.y = height * gridSizeI;


	map.reserve(maxSize.x);
	for (unsigned short x = 0; x < maxSize.x; x++)
	{
		map.emplace_back(std::vector<std::vector<std::vector<std::shared_ptr<Tile>>>>());
		map[x].reserve(maxSize.y);
		for (unsigned short y = 0; y < maxSize.y; y++)
		{
			map[x].emplace_back(std::vector<std::vector<std::shared_ptr<Tile>>>());
			map[x][y].reserve(layers);
			for (unsigned short z = 0; z < layers; z++)
			{
				map[x][y].emplace_back(std::vector<std::shared_ptr<Tile>>());
				map[x][y][z].reserve(map[x][y][z].size());
				for (size_t k = 0; k < map[x][y][z].size(); k++) {
					map[x][y][z].emplace_back(nullptr);
				}
			}
		}
	}

	
	if (!tileSheet.loadFromFile(texture_file))
		std::cout << "ERROR::TILEMAP::FAILED TO LOAD TILETEXTURESHEET " << '\n';

	collisionBox.setSize(sf::Vector2f(gridSizeF, gridSizeF));
	collisionBox.setFillColor(sf::Color::Transparent);
	collisionBox.setOutlineColor(sf::Color::Red);
	collisionBox.setOutlineThickness(1.f);


}

TileMap::~TileMap()
{
}

//Accessors
const int TileMap::getLayerSize(const int x, const int y, const int layer) const
{
	if (x >= 0 && x < static_cast<int>(map.size()))
	{
		if (y >= 0 && y < static_cast<int>(map[x].size()))
		{
			if (layer >= 0 && layer < static_cast<int>(map[x][y].size()))
			{
				return map[x][y][layer].size();
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
	for (unsigned short x = 0; x < maxSize.x; x++)
	{
		for (unsigned short y = 0; y < maxSize.y; y++)
		{
			for (unsigned short z = 0; z < layers; z++)
			{
				for (size_t k = 0; k < map[x][y][z].size(); k++) {
					if (!map[x][y][z].empty()) //sees if tile there to remove
					{
						map[x][y][z].pop_back();
					}
				}
			}
		}
	}
}

void TileMap::addTile(const int x, const int y, const int z, const sf::IntRect& texture_rect, const bool collision, const short type)
{
	//Take two indicies and checks to see if in array size.
	if (x >= 0 && x < maxSize.x && //x
		y >= 0 && y < maxSize.y && //y
		z >= 0 && z < layers)//z 
	{
		
			map[x][y][z].push_back(std::make_shared<Tile>(x * gridSizeF, y * gridSizeF, gridSizeF, tileSheet, texture_rect, collision, type));
	
	}
}

void TileMap::removeTile(const int x, const int y, const int z)
{
	//Take two indicies and checks to see if in array size.
	if (x >= 0 && x < maxSize.x && //x
		y >= 0 && y < maxSize.y && //y
		z >= 0 && z < layers)//z 
	{
		if (!map[x][y][z].empty()) //sees if tile there to remove
		{
			for (size_t k = 0; k < map[x][y][z].size(); k++)
				map[x][y][z].pop_back();
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
		of << maxSize.x << " " << maxSize.y << "\n"
			<< gridSizeI << "\n"
			<< layers << "\n"
			<< textureFile << "\n";
		for (unsigned short x = 0; x < maxSize.x; x++)
		{
			for (unsigned short y = 0; y < maxSize.y; y++)
			{
				for (unsigned short z = 0; z < layers; z++)
				{
					for (size_t k = 0; k < map[x][y][z].size(); k++) {
						if (!map[x][y][z].empty()) {
							if (map[x][y][z][k] != NULL) {
								of << x << " " << y << " " << z << " ";
								of << *map[x][y][z][k] << " ";
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
	clear();
	std::ifstream is;
	is.open(file_name);
	if (is.is_open())
	{
		//Map
		is >> maxSize.x >> maxSize.y
			>> gridSizeI
			>> layers
			>> textureFile;


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
				map[x][y][z].push_back(std::make_shared<Tile>(x * gridSizeF, y * gridSizeF, gridSizeF, tileSheet, texture_rect, collision, type));
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
	else if (entity->getPosition().x + entity->getGlobalBounds().width > maxSizeWorldI.x)
	{
		entity->setPosition(maxSizeWorldI.x - entity->getGlobalBounds().width, entity->getPosition().y);
		entity->stopVelocityX();
	}
	if (entity->getPosition().y < 0.f)
	{
		entity->setPosition(entity->getPosition().x, 0.f);
		entity->stopVelocityY();
	}
	else if (entity->getPosition().y + entity->getGlobalBounds().height > maxSizeWorldI.y)
	{
		entity->setPosition(entity->getPosition().x, maxSizeWorldI.y - entity->getGlobalBounds().height);
		entity->stopVelocityY();
	}
	
	layer = 0;
	//Render around the player
	fromX = entity->getGridPosition(gridSizeI).x - 5;
	if (fromX < 0)
		fromX = 0;
	else if (fromX > maxSizeWorldI.x)
		fromX = maxSizeWorldI.x;

	toX = entity->getGridPosition(gridSizeI).x + 6;
	if (toX < 0)
		toX = 0;
	else if (toX > maxSizeWorldI.x)
		toX = maxSizeWorldI.x;

	fromY = entity->getGridPosition(gridSizeI).y - 3;
	if (fromY < 0)
		fromY = 0;
	else if (fromY > maxSizeWorldI.y)
		fromY = maxSizeWorldI.y;

	toY = entity->getGridPosition(gridSizeI).y + 4;
	if (toY < 0)
		toY = 0;
	else if (toY > maxSizeWorldI.y)
		toY = maxSizeWorldI.y;
	//loop through nearby objects
	for (int x = fromX; x < toX; x++)
	{
		for (int y = fromY; y < toY; y++)
		{

			for (size_t k = 0; k < map[x][y][layer].size(); k++) {
				if (map[x][y][layer][k] != nullptr) {
					sf::FloatRect playerBounds = entity->getGlobalBounds();
					sf::FloatRect wallBounds = map[x][y][layer][k]->getGlobalBounds();
					sf::FloatRect nextPositionBounds = entity->getNextPositionBounds(dt);
					if (map[x][y][layer][k]->collision &&
						map[x][y][layer][k]->intersects(nextPositionBounds)
						)
					{
						//Bottom colision
			
						if (playerBounds.top < wallBounds.top
							&& playerBounds.top + playerBounds.height <= wallBounds.top + wallBounds.height
							&& playerBounds.left <= wallBounds.left + wallBounds.width - 1.f
							&& playerBounds.left + playerBounds.width >= wallBounds.left + 1.f
							)
						{
							entity->stopVelocityY();
							entity->setPosition(playerBounds.left, wallBounds.top - playerBounds.height - 1.f);
							
						}

						//Top collision
						if (playerBounds.top > wallBounds.top
							&& playerBounds.top + playerBounds.height > wallBounds.top + wallBounds.height
							&& playerBounds.left < wallBounds.left + wallBounds.width - 1.f
							&& playerBounds.left + playerBounds.width > wallBounds.left + 1.f
							)
						{
							entity->stopVelocityY();
							entity->setPosition(playerBounds.left, wallBounds.top + wallBounds.height + 1.f);
						}

						//Right collision
						if (playerBounds.left < wallBounds.left
							&& playerBounds.left + playerBounds.width < wallBounds.left + wallBounds.width
							&& playerBounds.top < wallBounds.top + wallBounds.height - 1.f
							&& playerBounds.top + playerBounds.height > wallBounds.top + 1.f
							)
						{
							entity->stopVelocityX();
							entity->setPosition(wallBounds.left - playerBounds.width - 1.f, playerBounds.top);
						}

						//Left collision
						if (playerBounds.left > wallBounds.left
							&& playerBounds.left + playerBounds.width > wallBounds.left + wallBounds.width
							&& playerBounds.top < wallBounds.top + wallBounds.height - 1.f
							&& playerBounds.top + playerBounds.height > wallBounds.top + 1.f
							)
						{
							entity->stopVelocityX();
							entity->setPosition(wallBounds.left + wallBounds.width + 1.f, playerBounds.top);
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

void TileMap::render(sf::RenderTarget& target, const sf::Vector2i& gridPosition, const sf::Vector2f playerPos, sf::Shader* shader, const bool show_collision)
{
		layer = 0;
		//Render boxes only around the player. (just enough to never show rendering on screen)
		fromX = gridPosition.x - 18;
		if (fromX < 0)
			fromX = 0;
		else if (fromX > maxSizeWorldI.x)
			fromX = maxSizeWorldI.x;

		toX = gridPosition.x + 18;
		if (toX < 0)
			toX = 0;
		else if (toX > maxSizeWorldI.x)
			toX = maxSizeWorldI.x;

		fromY = gridPosition.y - 10;
		if (fromY < 0)
			fromY = 0;
		else if (fromY > maxSizeWorldI.y)
			fromY = maxSizeWorldI.y;

		toY = gridPosition.y + 10;
		if (toY < 0)
			toY = 0;
		else if (toY > maxSizeWorldI.y)
			toY = maxSizeWorldI.y;

		for (int x = fromX; x < toX; x++)
		{
			for (int y = fromY; y < toY; y++)
			{
				for (size_t k = 0; k < map[x][y][layer].size(); k++) {
					if (map[x][y][layer][k] != NULL) {
						if (map[x][y][layer][k]->getType() == TileType::DEFERRED)
						{
							deferredRenderStack.push(map[x][y][layer][k]);
						}
						else {
							if(shader)
								map[x][y][layer][k]->render(target, playerPos, shader);
							else
								map[x][y][layer][k]->render(target);
						}

						if (map[x][y][layer][k]->getCollision()) {
							collisionBox.setPosition(map[x][y][layer][k]->getPosition());
							if(show_collision)
							target.draw(collisionBox);
						}
					}

				}
			}

		}
}


void TileMap::renderDeferred(sf::RenderTarget& target, const sf::Vector2f playerPos, sf::Shader* shader)
{
	while (!deferredRenderStack.empty())
	{
		if (shader)
			deferredRenderStack.top()->render(target, playerPos, shader);
		else
			deferredRenderStack.top()->render(target);
		deferredRenderStack.pop();
	}
}




