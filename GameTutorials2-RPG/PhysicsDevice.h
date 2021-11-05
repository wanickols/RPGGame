#pragma once
#include "box2d.h"
#include "Constants.h"

class Entity;
struct Vector2D;
struct GAME_PHYSICS;

class PhysicsDevice
{
public:
	
	PhysicsDevice(sf::Vector2f gravity);
	bool initialize();
	bool createFixture(std::shared_ptr<Entity> Entity, GAME_PHYSICS& physics);

	sf::Vector2f getPosition(std::shared_ptr<Entity> Entity);
	float getAngle(std::shared_ptr<Entity> Entity);

	void applyForce(std::shared_ptr<Entity> Entity, bool forward);
	void applyAngularForce(std::shared_ptr<Entity> Entity, bool right);

	bool update(float dt);
	b2Body* findBody(std::shared_ptr<Entity> Entity);

	bool removeEntity(std::shared_ptr<Entity> Entity);

	//conversions between phsysics world and SDL2
	sf::Vector2f PV2GV(b2Vec2 physicsVec);

	//Physics World to Real world. Since physics uses between 1-10
	inline float PW2RW(float x) { return x * fPRV; } //float to phsyics float
	inline float RW2PW(float x) { return x / fPRV; } //physics float to float
	inline float RW2PW(GAME_INT x) { return (float)x / fPRV; } //int to physics float
	inline float RW2PWAngle(float x) { return((float)x * (2.0f * PI) / 360.0f); } //degrees to radians
	inline float PW2RWAngle(float x) { return((float)x * 360.0f / (2.0f * PI)); } //radians to degrees

	//public just for creating borders!
	std::shared_ptr<b2World> world;
private:

	const b2Vec2 gravity;
	sf::Vector2f alignCenters(std::shared_ptr<Entity> Entity);
};

