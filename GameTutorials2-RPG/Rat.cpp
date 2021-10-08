#include "stdafx.h"
#include "Rat.h"

void Rat::initVariables()
{
	name = "Rat";
}

Rat::Rat(float x, float y, sf::Texture& texture, EnemySpawner& origin)
	: Enemy(x, y, texture, origin)
{
	initVariables();
}

void Rat::update(const float& dt, const sf::Vector2f mousePosView)
{
	animationComponent->play("DOWNIDLE", dt, false);
}

void Rat::render(sf::RenderTarget& target, sf::Shader* shader, sf::Vector2f light_position, const bool show_hitbox)
{
	if (shader) {
		shader->setUniform("hasTexture", true);
		shader->setUniform("lightPos", light_position);

		target.draw(sprite, shader);
	}
	else {
		target.draw(sprite);
	}
	if (show_hitbox)
		hitBoxComponent->render(target);

}
