#include "stdafx.h"
#include "Enemy.h"
#include "EnemySpawner.h"
#include "Item.h"
#include "ComponentInclude.h"

Enemy::Enemy()
{
}

Enemy::~Enemy()
{
}

void Enemy::update(const float& dt, const sf::Vector2f mousePosView)
{
	Entity::update(dt, mousePosView);
}

void Enemy::render(sf::RenderTarget& target, sf::Shader* shader, sf::Vector2f light_position, const bool show_hitbox)
{
	Entity::render(target, shader, light_position, show_hitbox);
}
