#pragma once
#include "Component.h"
class Movement;
class PhysicsDevice;
class AnimationC;
class Entity;
class Player;
class b2Body;

class UserInput : public Component
{
public:
	UserInput(Entity& owner);
	void shoot(const sf::Vector2f& mousePosView);
	void update(const float& dt, const sf::Vector2f mousePosView);
	void handleInput(std::map<std::string,int>& keybinds, const float& dt);
private:
	bool attacking;
	Player* player;
	Movement* movement;
	gui::KeyTimeManger keytimer;
	AnimationC* animation;
	b2Body* body;
};

