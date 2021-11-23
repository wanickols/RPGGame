#pragma once
#include "Component.h"
class Task;
class Entity;
class Blackboard;
class BehaviorTree;
class NPC :
	public Component
{
public:
	NPC(std::shared_ptr<Entity> owner);
	~NPC();

	void Initialize();

	void Start() {};
	void update(const float& dt, const sf::Vector2f mousePosView);
	void Finish();
private:
	std::shared_ptr<BehaviorTree> behaviorTree;
};

