#pragma once
#include "Entity.h"
#include "Tile.h"

namespace sf {
	class Texture;
	class RenderTarget;
	class RectangleShape;
}

class EnemyLibrary;
class Enemy;
class Graph;

class TileMap
{

private:

	
public:
	
	//Init Function
	void initTileMap(std::shared_ptr<PhysicsDevice> p_device);
	TileMap(float grid_size, int width, int height, std::string texture_file, std::shared_ptr<PhysicsDevice> p_device = nullptr);
	TileMap(const std::string file_name, std::shared_ptr<EnemyLibrary> enemyLib = NULL, std::shared_ptr<PhysicsDevice> p_device = nullptr);
	virtual ~TileMap();
	
	//Accessors
	const bool tileEmpty(const int x, const int y, const int layer) const;
	const int getLayerSize(const int x, const int y, const int layer) const;
	std::shared_ptr<Graph> getGraph();

	//Functions
	void clear();
	void addTile(const int x, const int y, const int z, const sf::IntRect& texture_rect, const bool collision, const short type);
	void addEnemyTile(const int x, const int y, const int z, const sf::IntRect& texture_rect, int enemy_type, int max_spawned, int time_to_spawn, float max_distance, int level);
	void removeTile(const int x, const int y, const int z, bool type_check = false);
	void saveToFile(const std::string file_name);
	void loadFromFile(const std::string file_name);
	void initLoadFromFile(const std::string& file_name);


	bool updateWorldBounds(std::shared_ptr<Entity> entity);

	void updateTiles(std::shared_ptr<Entity> entity, const float& dt, std::vector<std::shared_ptr<Enemy>>& enemies);
	
	void update(std::shared_ptr<Entity> entity, const float& dt);
	void render(sf::RenderTarget& Target, const sf::Vector2i& gridPosition, const sf::Vector2f player_position = sf::Vector2f(0.f, 0.f), sf::Shader* shader = NULL, const bool show_collision = false, const bool show_EnemySpawner = false);
	void renderDeferred(sf::RenderTarget& Target, const sf::Vector2f player_position = sf::Vector2f(0.f,0.f), sf::Shader* shader = NULL);

	//Accessors 
	const sf::Texture* getTileSheet() const;
	const sf::Vector2f& getMaxSizeF() const;


	//Culling
	int fromX;
	int toX;
	int fromY;
	int toY;
	int layer;

private:

	//Init Function

	sf::Vector2i maxSize;
	sf::Vector2i maxSizeWorldI;
	sf::Vector2f maxSizeWorldF;
	std::string textureFile;
	std::string enemySpawnerTextureFile;
	int layers;
	float gridSizeF;
	int gridSizeI;
	sf::Texture tileSheet;
	sf::Texture enemySpawner;
	sf::RectangleShape collisionBox;
	std::shared_ptr<EnemyLibrary> enemyLib;
	std::shared_ptr<PhysicsDevice> pDevice;
	std::shared_ptr<Graph> graph;
	std::shared_ptr<std::vector<sf::Vector2i>> obstacles;
	//   x            y				z(depth)
	std::vector < std::vector < std::vector < std::vector <std::shared_ptr<Tile>> > > > map;
	std::stack<std::shared_ptr<Tile>> deferredRenderStack;
	
};


