#pragma once
class Entity;
class EnemySpawner;
class Movement;
#include "Movement.h"

class AISetting
{
public:
	AISetting(std::string name, std::shared_ptr<Entity> entity, Entity& owner);
		
	virtual void update(const float& dt) = 0;
	virtual void reaction(const float& dt) {};
	const std::string& getName() const;
	gui::KeyTimeManger keytimer;
	void setUpdateMe(bool update);

protected:
	bool updateMe;

	std::string name;
	Entity& owner;
	std::shared_ptr<Entity> entity;
	std::shared_ptr<EnemySpawner> spawner;
	Movement* movement;

	/*std::shared_ptr<Graph> graph;
	std::shared_ptr<std::vector<sf::Vector2i>> obstacles;*/
	static std::random_device seed;
	static std::default_random_engine engine;

};

