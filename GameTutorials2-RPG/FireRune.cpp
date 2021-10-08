#include "stdafx.h"
#include "FireRune.h"
#include "Bullet.h"

FireRune::FireRune()
{	

	if (!bulletTexture.loadFromFile("Resources/Images/Sprites/Bullets/FIRE_BULLET.png")) {
		throw "ERROR::FIRERUNE::COULD_NOT_LOAD_FIRE_BULLET_TEXTURE \n";
	}
}

void FireRune::shoot(float playerX, float playerY, float playerVelX, float playerVelY, const unsigned short lastState)
{
	bullets.push_back(std::make_shared<Bullet>(playerX, playerY, playerVelX, playerVelY, bulletTexture, lastState));
}


void FireRune::update(const float& dt, const sf::Vector2f& mousePosView)
{

	//Bullets
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

void FireRune::render(sf::RenderTarget& target, sf::Shader* shader, sf::Vector2f light_position, const bool show_hitbox)
{
	//Rune
	
	//bullets
	if (shader) {
		for (auto& iter : bullets)
		{

			if (iter->getRunning())
				iter->render(target,shader, light_position, show_hitbox);
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
