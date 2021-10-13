#pragma once
class Component
{
public:
	Component();

	virtual void update(const float& dt, const sf::Vector2f mousePosView) = 0;
	virtual void render(sf::RenderTarget& target, sf::Shader* shader, sf::Vector2f light_position, const bool show_hitbox) = 0;
	const std::string& getName() const;

protected:
	std::string name;

private:


};

