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

	gui::KeyTimeManger keytimer;
private:
	std::shared_ptr<BehaviorTree> behaviorTree;
	bool* follow;
	std::shared_ptr<Entity> npcOwner;
};

