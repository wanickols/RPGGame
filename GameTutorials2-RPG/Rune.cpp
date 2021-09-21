#include "stdafx.h"
#include "Rune.h"
#include "Bullet.h"
#include "TileMap.h"


void Rune::updateBulletCollision(const float& dt, std::shared_ptr<TileMap> map)
{
	if (!bullets.empty()) {
		for (int i = 0; i < bullets.size(); i++) {
			map->updateCollision(bullets.at(i), dt);
		}
	}
}

const bool Rune::isBulletEmpty()
{
	return bullets.empty();
}
