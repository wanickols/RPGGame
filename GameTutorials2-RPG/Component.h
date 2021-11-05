#pragma once

class Entity;

class Component
{
public:
	Component(std::string name, Entity& owner);

	virtual void update(const float& dt, const sf::Vector2f mousePosView) = 0;
	virtual void render(sf::RenderTarget& target, sf::Shader* shader, sf::Vector2f light_position, const bool show_hitbox) {};
	const std::string& getName() const;
	Entity& getOwner() const;
protected:
	std::string name;
	Entity& owner;

private:


};

