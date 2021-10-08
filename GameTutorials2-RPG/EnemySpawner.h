#pragma once
#include "Tile.h"

class Enemy;

class EnemySpawner : public Tile
{
public:
	EnemySpawner(float x, float y, const sf::Texture& texture, const sf::IntRect& texture_rect, int enemy_type, int max_spawned, int time_to_spawn, float max_distance);
	void spawn();
	void update(const float& dt);
	void render(sf::RenderTarget& target, const sf::Vector2f player_position = sf::Vector2f(), sf::Shader* shader = NULL);
	
	//
	std::ofstream& getStringTile(std::ofstream& os) override;
	
	
	int timeToSpawn;
	int maxSpawned;
	int enemyType;
	float maxDistance;

private:
	sf::Vector2f position;
	std::vector<std::shared_ptr<Enemy>> enemies;
	
	
};

