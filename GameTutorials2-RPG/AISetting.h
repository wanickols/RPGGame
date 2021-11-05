#pragma once
class Entity;
class EnemySpawner;

class AISetting
{
public:
	AISetting(std::string name, std::shared_ptr<Entity> entity, Entity& owner)
		: owner(owner), name(name), entity(entity), spawner(nullptr) {};
	virtual void update(const float& dt) = 0;
	virtual void reaction() {};
	const std::string& getName() const;

protected:
	std::string name;
	Entity& owner;
	std::shared_ptr<Entity> entity;
	std::shared_ptr<EnemySpawner> spawner;
	static std::random_device seed;
	static std::default_random_engine engine;

};

