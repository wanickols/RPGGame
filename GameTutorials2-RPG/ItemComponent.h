#pragma once

class Item;

class ItemComponent abstract
{
public:
	ItemComponent(std::string componentName, Item& owner);
	const std::string getComponentName() const;
	virtual void update(const float& dt, const sf::Vector2f& mousePosView, const sf::Vector2f& position) = 0;
	virtual void render(sf::RenderTarget& target, sf::Shader* shader = NULL, sf::Vector2f light_position = sf::Vector2f(), const bool show_hitbox = false) {};
protected:
	std::shared_ptr<Item> owner;
private:
	std::string componentName;

};

