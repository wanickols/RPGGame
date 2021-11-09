#include "stdafx.h"
#include "RuneComponent.h"
#include "Bullet.h"
#include "TileMap.h"
#include "PhysicsDevice.h"
#include "bulletC.h"
#include "physicsComponent.h"

RuneComponent::RuneComponent(std::string bullet_path, Item& owner)
	: ItemComponent("rune", owner)
{

	if (!bulletTexture.loadFromFile(bullet_path)) {
		std::cout << "ERROR::RUNECOMPONENT::COULD_NOT_LOAD_BULLET_TEXTURE \n" << bullet_path << "\n";
	}
}

void RuneComponent::updateBulletCollision(const float& dt, std::shared_ptr<TileMap> map)
{

}

void RuneComponent::shoot(float playerX, float playerY, float playerVelX, float playerVelY, const unsigned short lastState, std::shared_ptr<PhysicsDevice> p_device)
{
	bullets.push_back(std::make_shared<Bullet>(playerX, playerY, playerVelX, playerVelY, bulletTexture, lastState));
	bullets.back()->getComponent<bulletC>()->initialize(p_device);
}

void RuneComponent::update(const float& dt, const sf::Vector2f& mousePosView, const sf::Vector2f& position)
{
	auto iter = bullets.begin();
	while (iter != bullets.end())
	{
		if (iter->get()->getComponent<bulletC>()->getRunning()) {
			iter->get()->update(dt, mousePosView);
			iter++;
		}
		else {
			//iter->get()->getComponent<physicsComponent>()->destroy();
			iter = bullets.erase(iter);
		}
	}
}

void RuneComponent::render(sf::RenderTarget& target, sf::Shader* shader, sf::Vector2f light_position, const bool show_hitbox)
{
	if (shader) {
		for (auto& iter : bullets)
		{

			if (iter->getComponent<bulletC>()->getRunning())
				iter->render(target, shader, light_position, show_hitbox);
		}
	}
	else {
		for (auto& iter : bullets)
		{

			if (iter->getComponent<bulletC>()->getRunning())
				iter->render(target);
		}
	}
}

const bool RuneComponent::isBulletEmpty()
{
	return bullets.empty();
}
