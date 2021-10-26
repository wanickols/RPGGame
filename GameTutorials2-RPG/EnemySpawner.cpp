#include "stdafx.h"
#include "EnemySpawner.h"
#include "Enemy.h"
#include "EnemyLibrary.h"
#include "enemyGui.h"

EnemySpawner::EnemySpawner(float x, float y, const sf::Texture& texture, const sf::IntRect& texture_rect, const sf::Texture& enemy_texture, int enemy_type, int max_spawned, int time_to_spawn, float max_distance, int enemy_level, std::shared_ptr<EnemyLibrary> lib)
	: Tile(x, y, texture, texture_rect, false, ENEMYSPAWNER), enemyTexture(enemy_texture), enemyType(enemy_type), maxSpawned(max_spawned), timeToSpawn(time_to_spawn), maxDistance(max_distance)
{
	enemyLib = lib;
	position.x = x;
	position.y = y;
	totalSpawned = 0;
	enemyLevel = enemy_level;
}

std::shared_ptr<Enemy> EnemySpawner::spawn()
{
	++totalSpawned;
	std::shared_ptr<Enemy> enemy = std::make_shared<Enemy>();

	//enemyLib->translateType(enemyType);

	enemyLib->createComponents(*enemy, "Rat", *this);

	


	return enemy;
}

void EnemySpawner::update(const float& dt)
{


}

void EnemySpawner::render(sf::RenderTarget& target, const sf::Vector2f player_position, sf::Shader* shader)
{
	target.draw(shape);
}

std::ofstream& EnemySpawner::getStringTile(std::ofstream& os)
{
	//Texture rect x y, type, collision
	os << type << " " << shape.getTextureRect().left << " " << shape.getTextureRect().top
		<< " " << collision << " " << enemyType << " " << maxSpawned << " " << timeToSpawn << " " << maxDistance << " " << enemyLevel;
	return os;
}

bool EnemySpawner::canSpawn()
{
	if (totalSpawned < maxSpawned)
		return true;
	else
		return false;
}
