#include "stdafx.h"
#include "EnemySpawner.h"
#include "Enemy.h"

EnemySpawner::EnemySpawner(float x, float y, const sf::Texture& texture, const sf::IntRect& texture_rect, int enemy_type, int max_spawned, int time_to_spawn, float max_distance)
	: Tile(x, y, texture, texture_rect, false, ENEMYSPAWNER), enemyType(enemy_type), maxSpawned(max_spawned), maxDistance(max_distance), timeToSpawn(time_to_spawn)
{
	

}

void EnemySpawner::spawn()
{
}

void EnemySpawner::update()
{
}

void EnemySpawner::render(sf::RenderTarget& target, const sf::Vector2f playerPosition, sf::Shader* shader)
{
	target.draw(shape);
}
