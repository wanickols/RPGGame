#include "stdafx.h"
#include "EnemySpawner.h"
#include "Enemy.h"

EnemySpawner::EnemySpawner(float x, float y, const sf::Texture& texture, const sf::IntRect& texture_rect, int enemy_type, int max_spawned, int time_to_spawn, float max_distance)
	: Tile(x, y, texture, texture_rect, false, ENEMYSPAWNER), enemyType(enemy_type), maxSpawned(max_spawned), timeToSpawn(time_to_spawn), maxDistance(max_distance)
{}

void EnemySpawner::spawn()
{
}

void EnemySpawner::update(const float& dt)
{
	for(auto& i : enemies)
	{
		i->update(dt);
	}

}

void EnemySpawner::render(sf::RenderTarget& target, const sf::Vector2f player_position, sf::Shader* shader)
{
	target.draw(shape);
}

std::ofstream& EnemySpawner::getStringTile(std::ofstream& os)
{
	//Texture rect x y, type, collision
	os << type << " " << shape.getTextureRect().left << " " << shape.getTextureRect().top
		<< " " << collision << " " << enemyType << " " << maxSpawned << " " << timeToSpawn << " " << maxDistance;
	return os;
}