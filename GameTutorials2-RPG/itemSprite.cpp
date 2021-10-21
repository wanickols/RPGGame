#include "stdafx.h"
#include "itemSprite.h"


itemSprite::itemSprite(sf::Sprite& sprite, sf::Texture& texture, int width, int height, Item& owner)
	: ItemComponent("sprite", owner)
{
	this->sprite = sprite;
	this->texture = texture;
	this->width = width;
	this->height = height;
}

const sf::Sprite& itemSprite::getSprite()
{
	// TODO: insert return statement here
	return sprite;
}

const sf::Texture& itemSprite::getTexture()
{
	// TODO: insert return statement here
	return texture;
}
