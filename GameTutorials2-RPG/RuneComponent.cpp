#include "stdafx.h"
#include "RuneComponent.h"
#include "Bullet.h"
#include "TileMap.h"

RuneComponent::RuneComponent(std::string bullet_path, Item& owner)
	: ItemComponent("rune", owner)
{

	if (!bulletTexture.loadFromFile(bullet_path)) {
		std::cout << "ERROR::RUNECOMPONENT::COULD_NOT_LOAD_BULLET_TEXTURE \n" << bullet_path << "\n";
	}
}

void RuneComponent::updateBulletCollision(const float& dt, std::shared_ptr<TileMap> map)
{
	if (!bullets.empty()) {
		auto it = bullets.begin();
		bullets.erase(std::remove_if(bullets.begin(), bullets.end(), [&](auto iter) {
			return map->updateTileCollision(iter, dt) || map->updateWorldBounds(iter);
			}

		), bullets.end()

				);
	}
	else
		bullets.clear();
}

void RuneComponent::shoot(float playerX, float playerY, float playerVelX, float playerVelY, const unsigned short lastState)
{
	bullets.push_back(std::make_shared<Bullet>(playerX, playerY, playerVelX, playerVelY, bulletTexture, lastState));
}

void RuneComponent::update(const float& dt, const sf::Vector2f& mousePosView, const sf::Vector2f& position)
{
	auto iter = bullets.begin();
	while (iter != bullets.end())
	{
		if (iter->get()->getRunning()) {
			iter->get()->update(dt, mousePosView);
			iter++;
		}
		else
			iter = bullets.erase(iter);
	}
}

void RuneComponent::render(sf::RenderTarget& target, sf::Shader* shader, sf::Vector2f light_position, const bool show_hitbox)
{
	if (shader) {
		for (auto& iter : bullets)
		{

			if (iter->getRunning())
				iter->render(target, shader, light_position, show_hitbox);
		}
	}
	else {
		for (auto& iter : bullets)
		{

			if (iter->getRunning())
				iter->render(target);
		}
	}
}

const bool RuneComponent::isBulletEmpty()
{
	return bullets.empty();
}
