#pragma once
#include "Tile.h"

class Enemy;
class EnemyLibrary;

class EnemySpawner : public Tile
{
public:
	EnemySpawner(float x, float y, sf::Texture& texture, const sf::IntRect& texture_rect, std::shared_ptr<Graph> graph, const sf::Texture& enemy_texture, int enemy_type, int max_spawned, sf::Int32 time_to_spawn, float max_distance, int enemy_level, std::shared_ptr<EnemyLibrary> lib, std::shared_ptr<PhysicsDevice> p_device);
	std::shared_ptr<Enemy> spawn();
	void update(const float& dt);
	void render(sf::RenderTarget& target, const sf::Vector2f player_position = sf::Vector2f(), sf::Shader* shader = NULL) override;
	
	//
	std::ofstream& getStringTile(std::ofstream& os) override;
	void reduceTotalSpawned();
	bool canSpawn();
	
	int totalSpawned;
	sf::Int32 timeToSpawn;
	int maxSpawned;
	int enemyType;
	float maxDistance;
	int enemyLevel;

private:
	sf::Vector2f position;
	sf::Clock enemySpawnTimer;
	sf::Texture enemyTexture;
	
	std::shared_ptr<EnemyLibrary> enemyLib;
	
};

