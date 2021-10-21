#include "stdafx.h"
#include "Item.h"
#include "ItemComponent.h"

Item::Item()
{
	componentList["info"] = false;
	componentList["sprite"] = false;
	componentList["weapon"] = false;
	componentList["rune"] = false;
}

void Item::addItemComponent(std::shared_ptr<ItemComponent> component)
{
	if (!componentList.find(component->getComponentName())->second) { //checks if component exist already
		components.push_back(component);
	}
	else
		std::cout << "ITEMCOMPONENT already exist" << std::endl;
}

void Item::update(const float& dt, const sf::Vector2f& mousePosView, const sf::Vector2f& position)
{
	for (auto& i : components)
	{
		i->update(dt, mousePosView, position);
	}
}

void Item::render(sf::RenderTarget& target, sf::Shader* shader, sf::Vector2f light_position, const bool show_hitbox)
{
	for (auto& i : components)
	{
		i->render(target, shader, light_position, show_hitbox);
	}
}

Item* Item::clone()
{
	return new Item(*this);;
}

