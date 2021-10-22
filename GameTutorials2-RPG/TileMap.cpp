#include "stdafx.h"
#include "Tile.h"
#include "EnemySpawner.h"
#include "Entity.h"
#include "Enemy.h"
#include "EnemyLibrary.h"
#include "TileMap.h"

void TileMap::initTileMap()
{
	
	
}

TileMap::TileMap(float grid_size, int width, int height, std::string texture_file)
	: textureFile(texture_file), fromX(0), toX(0), fromY(0), toY(0), layer(0)
{
	

	//enemySpawner.loadFromFile("Resources/Images/Tiles/EnemyTile");

	if (!tileSheet.loadFromFile(texture_file))
		std::cout << "ERROR::TILEMAP::FAILED TO LOAD TILETEXTURESHEET " << '\n';

	

	gridSizeF = grid_size;
	gridSizeI = static_cast<int>(grid_size);
	layers = 1;
	maxSize = { width, height };
	maxSizeWorldF.x = static_cast<float>(width) * gridSizeF;
	maxSizeWorldF.y = static_cast<float>(height) * gridSizeF;
	maxSizeWorldI.x = width * gridSizeI;
	maxSizeWorldI.y = height * gridSizeI;


	collisionBox.setSize(sf::Vector2f(gridSizeF, gridSizeF));
	collisionBox.setFillColor(sf::Color::Transparent);
	collisionBox.setOutlineColor(sf::Color::Red);
	collisionBox.setOutlineThickness(1.f);


}

TileMap::TileMap(const std::string file_name, std::shared_ptr<EnemyLibrary> enemy_lib)
: fromX(0), toX(0), fromY(0), toY(0), layer(0)
{
	enemyLib = enemy_lib;

	initLoadFromFile(file_name);

	gridSizeF = (float)gridSizeI;
	maxSizeWorldF.x = static_cast<float>(maxSize.x) * gridSizeF;
	maxSizeWorldF.y = static_cast<float>(maxSize.y) * gridSizeF;
	maxSizeWorldI.x = maxSize.x * gridSizeI;
	maxSizeWorldI.y = maxSize.y * gridSizeI;

	//if (!tileSheet.loadFromFile(textureFile))
		//std::cout << "ERROR::TILEMAP::FAILED TO LOAD TILETEXTURESHEET " << '\n';

	collisionBox.setSize(sf::Vector2f(gridSizeF, gridSizeF));
	collisionBox.setFillColor(sf::Color::Transparent);
	collisionBox.setOutlineColor(sf::Color::Red);
	collisionBox.setOutlineThickness(1.f);
}

TileMap::~TileMap()
{
}

const bool TileMap::tileEmpty(const int x, const int y, const int layer) const
{
	if (x >= 0 && x < static_cast<int>(map.size()))
	{
		if (y >= 0 && y < static_cast<int>(map[x].size()))
		{
			if (layer >= 0 && layer < static_cast<int>(map[x][y].size()))
			{
				return map[x][y][layer].empty();
			}
		}
	}
	
	return false;
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

const sf::Vector2f& TileMap::getMaxSizeF() const
{
	return maxSizeWorldF;
}


//Functions
void TileMap::clear()
{
	if (!map.empty()) {
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
}

void TileMap::addTile(const int x, const int y, const int z, const sf::IntRect& texture_rect, const bool collision, const short type)
{
	//Take two indicies and checks to see if in array size.
	if (x >= 0 && x < maxSize.x && //x
		y >= 0 && y < maxSize.y && //y
		z >= 0 && z < layers)//z 
	{
			map[x][y][z].push_back(std::make_shared<Tile>(x * gridSizeF, y * gridSizeF, tileSheet, texture_rect, collision, type));
	}
}

void TileMap::addEnemyTile(const int x, const int y, const int z, const sf::IntRect& texture_rect, int enemy_type, int max_spawned, int time_to_spawn, float max_distance)
{
	
	//Take two indicies and checks to see if in array size.
	if (x >= 0 && x < maxSize.x && //x
		y >= 0 && y < maxSize.y && //y
		z >= 0 && z < layers)//z 
	{
			map[x][y][z].push_back(std::make_shared<EnemySpawner>(x * gridSizeF, y * gridSizeF, tileSheet, texture_rect, *enemyLib->find(enemyLib->translateType(enemy_type)), enemy_type, max_spawned, time_to_spawn, max_distance, enemyLib));
	}
}

void TileMap::removeTile(const int x, const int y, const int z, bool type_check)
{
	

		if (x >= 0 && x < maxSize.x && //x
			y >= 0 && y < maxSize.y && //y
			z >= 0 && z < layers)//z 
		{
			if (!map[x][y][z].empty()) //sees if tile there to remove
			{
				if (type_check) {
					switch (map[x][y][z].back()->getType())
					{
					case(ENEMYSPAWNER):
						break;
					default:
						return;
						break;
					}
				}
				for (size_t k = 0; k < map[x][y][z].size(); k++)
					map[x][y][z].pop_back();
			}
		}
		
	
	//Take two indicies and checks to see if in array size.
		
	
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
	type,Texture rect x y, collision
	x y z
	EnemyTiles:
	type,Texture rect x y, collision
	enemy_type, max_spawned, time_to_spawn, max_distance
	x y z
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
								switch (map[x][y][z][k]->getType()) 
								{
								case(TileType::ENEMYSPAWNER):
									map[x][y][z][k]->getStringTile(of);
									of << " " << x << " " << y << " " << z << "\n";
									of;
									break;
								default:
									map[x][y][z][k]->getStringTile(of);
									of << " " << x << " " << y << " " << z << "\n";
									break;
								}
							
								
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
		short type;
		int x;
		int y;
		int z;
		int trX;
		int trY;
		bool collision;
		

		while (is >> type >> trX >> trY >> collision) {
			sf::IntRect texture_rect;
			texture_rect.left = trX; texture_rect.top = trY;
			texture_rect.width = (int)gridSizeF; texture_rect.height = (int)gridSizeF;

			switch(type)
			{
			case(TileType::ENEMYSPAWNER):
				int enemy_type, max_spawned, time_to_spawn;
				float max_distance;
				is >> enemy_type >> max_spawned >> time_to_spawn >> max_distance
					>> x >> y >> z;
				map[x][y][z].emplace_back(std::make_shared<EnemySpawner>(x * gridSizeF, y * gridSizeF, tileSheet, texture_rect, *enemyLib->find(enemyLib->translateType(enemy_type)), enemy_type, max_spawned, time_to_spawn, max_distance, enemyLib));
				break;
			default:
				//std::cout << x << y << z << trX << trY << collision << type
				is >> x >> y >> z;
				map[x][y][z].emplace_back(std::make_shared<Tile>(x * gridSizeF, y * gridSizeF, tileSheet, texture_rect, collision, type));
				break;
			}
		}
	}
	else
	{
		std::cout << "TILEMAP LOAD COULD OPEN TILEMAP FILE: " << file_name << "\n";
	}
	is.close();
}

void TileMap::initLoadFromFile(const std::string& file_name)
{
	std::ifstream is;
	is.open(file_name);
	if (is.is_open())
	{
		//Map
		is >> maxSize.x >> maxSize.y
			>> gridSizeI
			>> layers
			>> textureFile;
		gridSizeF = (float)gridSizeI;
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

		if (!tileSheet.loadFromFile(textureFile))
			std::cout << "ERROR::TILEMAP::FAILED TO LOAD TILETEXTURESHEET " << '\n';
	}
	is.close();
	loadFromFile(file_name);
	
}

bool TileMap::updateWorldBounds(std::shared_ptr<Entity> entity)
{
//WORLD BOUNDS
if (entity->getPosition().x < 0.f)
{
	entity->setPosition(0.f, entity->getPosition().y);
	entity->stopVelocityX();
	return true;
}
else if (entity->getPosition().x + entity->getGlobalBounds().width > maxSizeWorldI.x)
{
	entity->setPosition(maxSizeWorldI.x - entity->getGlobalBounds().width, entity->getPosition().y);
	entity->stopVelocityX();
	return true;
}
if (entity->getPosition().y < 0.f)
{
	entity->setPosition(entity->getPosition().x, 0.f);
	entity->stopVelocityY();
	return true;
}
else if (entity->getPosition().y + entity->getGlobalBounds().height > maxSizeWorldI.y)
{
	entity->setPosition(entity->getPosition().x, maxSizeWorldI.y - entity->getGlobalBounds().height);
	entity->stopVelocityY();
	return true;
}
return false;
}

bool TileMap::updateTileCollision(std::shared_ptr<Entity> entity, const float& dt)
{
	layer = 0;
	//Update around the player
	fromX = entity->getGridPosition(gridSizeI).x - 1;
	if (fromX < 0)
		fromX = 0;
	else if (fromX > gridSizeI)
		fromX = gridSizeI;

	toX = entity->getGridPosition(gridSizeI).x + 2;
	if (toX < 0)
		toX = 0;
	else if (toX > gridSizeI)
		toX = gridSizeI;

	fromY = entity->getGridPosition(gridSizeI).y - 1;
	if (fromY < 0)
		fromY = 0;
	else if (fromY > gridSizeI)
		fromY = gridSizeI;

	toY = entity->getGridPosition(gridSizeI).y + 2;
	if (toY < 0)
		toY = 0;
	else if (toY > gridSizeI)
		toY = gridSizeI;
	//loop through nearby objects
	for (int x = fromX; x < toX; x++)
	{
		for (int y = fromY; y < toY; y++)
		{

			for (size_t k = 0; k < map[x][y][layer].size(); k++) {
				if (map[x][y][layer][k] != nullptr) {

					map[x][y][layer][k]->update(dt);

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
							&& playerBounds.left < wallBounds.left + wallBounds.width - 1.f
							&& playerBounds.left + playerBounds.width >= wallBounds.left + 1.f
							)
						{
							entity->stopVelocityY();
							entity->setPosition(playerBounds.left, wallBounds.top - playerBounds.height - 1.f);
							return true;
						}

						
						//Top collision
						if (playerBounds.top > wallBounds.top 
							&& playerBounds.top + playerBounds.height >= wallBounds.top + wallBounds.height 
							&& playerBounds.left < wallBounds.left + wallBounds.width - 1.f 
							&& playerBounds.left + playerBounds.width > wallBounds.left  + 1.f
							)
						{
							entity->stopVelocityY();
							entity->setPosition(playerBounds.left, wallBounds.top + wallBounds.height + 1.f);
							return true;
						}
						

						//Right collision
						if (playerBounds.left < wallBounds.left
							&& playerBounds.left + playerBounds.width <= wallBounds.left + wallBounds.width
							&& playerBounds.top < wallBounds.top + wallBounds.height  - 1.f
							&& playerBounds.top + playerBounds.height > wallBounds.top +1.f
							)
						{
							entity->stopVelocityX();
							entity->setPosition(wallBounds.left - playerBounds.width - 1.f, playerBounds.top);
							return true;
						}


						//Left collision
						if (playerBounds.left > wallBounds.left
							&& playerBounds.left + playerBounds.width >= wallBounds.left + wallBounds.width
							&& playerBounds.top < wallBounds.top + wallBounds.height -1.f
							&& playerBounds.top + playerBounds.height > wallBounds.top + 1.f
							)
						{
							entity->stopVelocityX();
							entity->setPosition(wallBounds.left + wallBounds.width + 1.f, playerBounds.top);
							return true;
						}
					}
				}
			}
		}

	}
	return false;
}

void TileMap::updateTiles(std::shared_ptr<Entity> entity, const float& dt, std::vector<std::shared_ptr<Enemy>>& enemies)
{
	layer = 0;
	//Update around the player
	fromX = entity->getGridPosition(gridSizeI).x - 23;
	if (fromX < 0)
		fromX = 0;
	else if (fromX > gridSizeI)
		fromX = gridSizeI;

	toX = entity->getGridPosition(gridSizeI).x + 23;
	if (toX < 0)
		toX = 0;
	else if (toX > gridSizeI)
		toX = gridSizeI;

	fromY = entity->getGridPosition(gridSizeI).y - 17;
	if (fromY < 0)
		fromY = 0;
	else if (fromY > gridSizeI)
		fromY = gridSizeI;

	toY = entity->getGridPosition(gridSizeI).y + 17;
	if (toY < 0)
		toY = 0;
	else if (toY > gridSizeI)
		toY = gridSizeI;
	//loop through nearby objects
	for (int x = fromX; x < toX; x++)
	{
		for (int y = fromY; y < toY; y++)
		{

			for (size_t k = 0; k < map[x][y][layer].size(); k++) {
				if (map[x][y][layer][k] != nullptr) {
					if (map[x][y][layer][k]->getType() == TileType::ENEMYSPAWNER) 
					{
						EnemySpawner* es = dynamic_cast<EnemySpawner*>(map[x][y][layer][k].get());
						if(es)
						{
							if (es->canSpawn())
								enemies.push_back(es->spawn());
						}
					}	
						map[x][y][layer][k]->update(dt);
					}
				}
			}
		}

}



void TileMap::update(std::shared_ptr<Entity> entity, const float& dt)
{
	updateTileCollision(entity, dt);
	updateWorldBounds(entity);
	//updateTiles(entity, dt);
}


void TileMap::render(sf::RenderTarget& target, const sf::Vector2i& gridPosition, const sf::Vector2f playerPos, sf::Shader* shader, const bool show_collision, const bool show_EnemySpawner)
{
		layer = 0;
		//Render boxes only around the player. (just enough to never show rendering on screen)
		fromX = gridPosition.x - 23;
		if (fromX < 0)
			fromX = 0;
		else if (fromX > gridSizeI)
			fromX = gridSizeI;

		toX = gridPosition.x + 23;
		if (toX < 0)
			toX = 0;
		else if (toX > gridSizeI)
			toX = gridSizeI;

		fromY = gridPosition.y - 17;
		if (fromY < 0)
			fromY = 0;
		else if (fromY > maxSizeWorldI.y)
			fromY = gridSizeI;

		toY = gridPosition.y + 17;
		if (toY < 0)
			toY = 0;
		else if (toY > gridSizeI)
			toY = gridSizeI;


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
							if (show_EnemySpawner) { //Enemy Spawners rendered or not
								if (shader)
									map[x][y][layer][k]->render(target, playerPos, shader);
								else
									map[x][y][layer][k]->render(target);
							}
							else {
								if (map[x][y][layer][k]->getType() != TileType::ENEMYSPAWNER) {
									if (shader)
										map[x][y][layer][k]->render(target, playerPos, shader);
									else
										map[x][y][layer][k]->render(target);
								}
							}
						}

						if (map[x][y][layer][k]->getCollision()) { //Collision box rendered or not
							collisionBox.setPosition(map[x][y][layer][k]->getPosition());
							if (show_collision)
								target.draw(collisionBox);
						}

					
					
					}

				}
			}

		}
}


void TileMap::renderDeferred(sf::RenderTarget& target, const sf::Vector2f player_position, sf::Shader* shader)
{
	while (!deferredRenderStack.empty())
	{
		if (shader)
			deferredRenderStack.top()->render(target, player_position, shader);
		else
			deferredRenderStack.top()->render(target);
		deferredRenderStack.pop();
	}
}




