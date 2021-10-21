#pragma once
#include "ItemComponent.h"
class itemSprite : public ItemComponent
{
public:
	itemSprite(sf::Sprite& sprite, sf::Texture& texture, int width, int height, Item& owner);
	
	void update(const float& dt, const sf::Vector2f& mousePosView, const sf::Vector2f& position) {};
	void render(sf::RenderTarget& target, sf::Shader* shader = NULL, sf::Vector2f light_position = sf::Vector2f(), const bool show_hitbox = false) {};
	const sf::Sprite& getSprite();
	const sf::Texture& getTexture();

	void initVaribles() {};
private:
	int width;
	int height;
	sf::Sprite sprite;
	sf::Texture texture;
};

