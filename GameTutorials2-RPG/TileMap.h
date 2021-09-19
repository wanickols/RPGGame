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

private:

	//Init Function
	void initTileMap();
public:
	
	TileMap(float grid_size, int width, int height, std::string texture_file);
	TileMap(const std::string file_name);
	virtual ~TileMap();
	
	//Accessors
	const bool tileEmpty(const int x, const int y, const int layer) const;
	const int getLayerSize(const int x, const int y, const int layer) const;

	//Functions
	void clear();
	void addTile(const int x, const int y, const int z, const sf::IntRect& texture_rect, const bool collision, const short type);
	void removeTile(const int x, const int y, const int z);
	void saveToFile(const std::string file_name);
	void loadFromFile(const std::string file_name);
	void initLoadFromFile(const std::string& file_name);

	void updateCollision(std::shared_ptr<Entity> entity, const float& dt);
	
	void update();
	void render(sf::RenderTarget& Target, const sf::Vector2i& gridPosition, const sf::Vector2f playerPos = sf::Vector2f(0.f, 0.f), sf::Shader* shader = NULL, const bool show_collision = false);
	void renderDeferred(sf::RenderTarget& Target, const sf::Vector2f playerPos = sf::Vector2f(0.f,0.f), sf::Shader* shader = NULL);

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
	int layers;
	float gridSizeF;
	int gridSizeI;
	sf::Texture tileSheet;
	sf::RectangleShape collisionBox;
	//   x            y				z(depth)
	std::vector < std::vector < std::vector < std::vector <std::shared_ptr<Tile>> > > > map;
	std::stack<std::shared_ptr<Tile>> deferredRenderStack;
	
};


