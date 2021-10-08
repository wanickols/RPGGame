#include "stdafx.h"
#include "Enemy.h"
#include "EnemySpawner.h"
#include "Item.h"

Enemy::Enemy(float x, float y, sf::Texture& texture, EnemySpawner& origin)
{
	setPosition(x, y);
	Origin = std::make_unique<EnemySpawner>(origin);
}

Enemy::~Enemy()
{
}
