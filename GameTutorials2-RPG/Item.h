#pragma once
class Item
{
public:
	Item();
	virtual void render(sf::RenderTarget& target, sf::Shader* shader = NULL, sf::Vector2f light_position = sf::Vector2f(), const bool show_hitbox = false) = 0;
protected:
	sf::Texture texture;
	sf::Sprite sprite;

private:
};

