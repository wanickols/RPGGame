#pragma once

class ItemComponent;

enum ItemClasses { BASIC = 0, RUNE, MELEE, MATERIAL, ORE };

class Item
{
public:
	Item();
	void update(const float& dt, const sf::Vector2f& mousePosView, const sf::Vector2f& position);
	virtual void render(sf::RenderTarget& target, sf::Shader* shader = NULL, sf::Vector2f light_position = sf::Vector2f(), const bool show_hitbox = false);
	virtual Item* clone();



	//Component Functions
	template<class T>
	T* getItemComponent()
	{
		for (auto comp : components)
		{
			T* target = nullptr;
			if (target = dynamic_cast<T*>(comp.get()))
			{
				return target;
			}
		}
		return (nullptr);
	}
	void addItemComponent(std::shared_ptr<ItemComponent> component);

protected:
private:
	std::vector<std::shared_ptr<ItemComponent>> components;
	std::map<std::string, bool> componentList;
};

