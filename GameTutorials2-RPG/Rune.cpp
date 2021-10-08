#include "stdafx.h"
#include "Rune.h"
#include "Bullet.h"
#include "TileMap.h"


void Rune::updateBulletCollision(const float& dt, std::shared_ptr<TileMap> map)
{
	if (!bullets.empty()) {
		for (int i = 0; i < bullets.size(); i++) {
			map->updateTileCollision(bullets.at(i), dt);
			map->updateWorldBounds(bullets.at(i));
		}
	}
}

const bool Rune::isBulletEmpty()
{
	return bullets.empty();
}
