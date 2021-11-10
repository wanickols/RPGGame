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
	PhysicsDevice(float gravityX, float gravityY);


	bool initialize();

	bool createEdge(sf::Vector2f start, sf::Vector2f finish);
	bool createBorders(sf::Vector2f dimensions, sf::Vector2f centerPos);
	bool createFixture(Entity& Entity, GAME_PHYSICS& physics);

	sf::Vector2f getPosition(Entity& Entity);
	float getAngle(Entity& Entity);

	void applyForce(Entity& Entity, sf::Vector2f direction);
	void applyAngularForce(Entity& entity , bool right);

	bool update(const float& dt);
	b2Body* findBody(Entity& Entity);

	bool removeEntity(Entity& Entity);

	//conversions between phsysics world and SDL2
	sf::Vector2f PV2GV(b2Vec2 physicsVec);
	b2Vec2 GV2PV(sf::Vector2f physicsVec);

	//Physics World to Real world. Since physics uses between 1-10
	inline float PW2RW(float x) { return x * fPRV; } //float to phsyics float
	inline float RW2PW(float x) { return x / fPRV; } //physics float to float
	inline float RW2PW(GAME_INT x) { return (float)x / fPRV; } //int to physics float
	inline float RW2PWAngle(float x) { return((float)x * (2.0f * PI) / 360.0f); } //degrees to radians
	inline float PW2RWAngle(float x) { return((float)x * 360.0f / (2.0f * PI)); } //radians to degrees

	void setVelocity(Entity& entity, sf::Vector2f velocity);

	void render(bool debug);
	//public just for creating borders!
	std::shared_ptr<b2World> world;

private:
	b2Vec2 gravity;
	sf::Vector2f alignCenters(Entity& Entity);
};

