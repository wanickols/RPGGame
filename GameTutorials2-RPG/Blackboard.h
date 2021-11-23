
#pragma once
#include "Constants.h"
class Entity;
class Blackboard
{
public:
	Blackboard();
	~Blackboard();
	std::shared_ptr<sf::Vector2f> playerPosition;
	std::map<std::shared_ptr<Entity>, sf::Vector2f> enemyOrigins;
	std::vector<std::shared_ptr<Entity>> objects;
	bool attack;
};

