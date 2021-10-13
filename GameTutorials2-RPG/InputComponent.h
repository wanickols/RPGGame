#pragma once
#include "Component.h"
class Entity;
class Player;
class InputComponent : public Component
{
public:
	InputComponent(Entity* owner);
	void shoot(const sf::Vector2f& mousePosView);
	void update(const float& dt, const sf::Vector2f mousePosView);
private:
	bool attacking;
	Player* player;
};

