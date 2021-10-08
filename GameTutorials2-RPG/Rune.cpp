#include "stdafx.h"
#include "Rune.h"
#include "Bullet.h"
#include "TileMap.h"


void Rune::updateBulletCollision(const float& dt, std::shared_ptr<TileMap> map)
{
	if (!bullets.empty()) {
		auto it = bullets.begin();
		bullets.erase(std::remove_if(bullets.begin(), bullets.end(), [&](auto iter) {
			return map->updateTileCollision(iter, dt) || map->updateWorldBounds(iter);
			}

		), bullets.end()

				);

	}
}

const bool Rune::isBulletEmpty()
{
	return bullets.empty();
}
