#include "stdafx.h"
#include "PhysicsDevice.h"
#include "Entity.h"
#include "AnimationC.h"
#include "ContactListener.h"

PhysicsDevice::PhysicsDevice(sf::Vector2f gravity)
{
	this->gravity.x = gravity.x;
	this->gravity.y = gravity.y;

}

PhysicsDevice::PhysicsDevice(float gravityX, float gravityY)
{
	this->gravity.x = gravityX;
	this->gravity.y = gravityY;
}

//**************************************
//Creates a new world on initialization
bool PhysicsDevice::initialize()
//**************************************
{
	world = std::make_shared<b2World>(gravity);
	if (world == nullptr) return false;
	
	std::unique_ptr<ContactListener> contactListener = std::make_unique<ContactListener>();
	world->SetContactListener(contactListener.release());

	return true;
}
//**************************************
//Steps the physics world
//
bool PhysicsDevice::update(const float& dt)
//**************************************
{
	// 8 3 accepted good values, can play later maybe
	world->Step(dt, 8, 3);
	world->DebugDraw();
	return true;

}


bool PhysicsDevice::createEdge(sf::Vector2f start, sf::Vector2f finish)
{
	b2BodyDef bd;
	bd.type = b2_staticBody;
	

	b2Body* edge = world->CreateBody(&bd);
	
	
	b2EdgeShape shape;
	shape.SetTwoSided(GV2PV(start), GV2PV(finish));
	
	edge->CreateFixture(&shape, 0.0f);

	return true;
}

bool PhysicsDevice::createBorders(sf::Vector2f dimensions, sf::Vector2f centerPosition)
{
	b2BodyDef bd;
	bd.type = b2_staticBody;

	b2Body* edge = world->CreateBody(&bd);

	b2PolygonShape shape;
	b2FixtureDef shapefd;
	
	shape.SetAsBox(dimensions.x/2,dimensions.y/2, GV2PV(centerPosition), 0.f);
	shapefd.shape = &shape;

	shapefd.density = 0.0f;
	shapefd.friction = .5f;
	shapefd.restitution = .3f;

	edge->CreateFixture(&shapefd);

	return true;
}

bool PhysicsDevice::createFixture(Entity& entity, GAME_PHYSICS& physics)
{
	//need the sprite component first!
	if (entity.getComponent<AnimationC>() == nullptr) return false;
	//new body definition
	std::unique_ptr<b2BodyDef> bd = std::make_unique<b2BodyDef>();

	//set body type based our games enum of body types
	switch (physics.bodyType)
	{
	case GAME_STATIC:
		bd->type = b2_staticBody;
		break;
	case GAME_KINEMATIC:
		bd->type = b2_kinematicBody;
		break;
	case GAME_DYNAMIC:
		bd->type = b2_dynamicBody;
		break;
	}

	bd->userData.pointer = reinterpret_cast<uintptr_t>(&entity);

	//divides by 2 to center it
	sf::Vector2f position{ entity.getComponent<AnimationC>()->getSprite().getPosition().x + entity.getComponent<AnimationC>()->getSprite().getGlobalBounds().width, entity.getComponent<AnimationC>()->getSprite().getPosition().y + entity.getComponent<AnimationC>()->getSprite().getGlobalBounds().height};

	//positions
	bd->position.Set(RW2PW(position.x), RW2PW(position.y));
	bd->angle = RW2PWAngle(physics.angle);
	bd->bullet = physics.bullet;

	//make body
	b2Body* body = world->CreateBody(bd.release());
	
	//dampening
	body->SetAngularDamping(physics.angularDamping);
	body->SetLinearDamping(physics.linearDamping);

	//***********************************FIXTURE*****************************************

	//Fixture definition
	b2FixtureDef shapefd;
	//made need one or the other, depending on what was passed.
	b2PolygonShape pShape;
	b2CircleShape cShape;

	float width = (entity.getComponent<AnimationC>()->getSprite().getGlobalBounds().width - 24) / 2.0f;
	float height = (entity.getComponent<AnimationC>()->getSprite().getGlobalBounds().height - 24)/ 2.0f;
	//Set fixture's shape
	switch (physics.objectShape)
	{
	case GAME_RECTANGLE:
		//rectangle's dimensions
		pShape.SetAsBox(RW2PW(width), RW2PW(height));
		shapefd.shape = &pShape;
		break;
	case GAME_CIRCLE:
		//circle radius based on object's width.
		

		if (width > height)	cShape.m_radius = (RW2PW(width));
		else cShape.m_radius = (RW2PW(height));
		shapefd.shape = &cShape;
		break;
	}

	//set fixture values based on passed in values.
	shapefd.density = physics.density;
	shapefd.friction = physics.friction;
	shapefd.restitution = physics.restitution;

	//create the fixture on the body.
	body->CreateFixture(&shapefd);
	body->SetEnabled(physics.physicsOn);

	return true;
}

sf::Vector2f PhysicsDevice::getPosition(Entity& entity)
{
	return(alignCenters(entity));
}

float PhysicsDevice::getAngle(Entity& entity)
{
	return (PW2RWAngle(findBody(entity)->GetAngle()));
}

void PhysicsDevice::applyForce(Entity& entity, sf::Vector2f direction)
{
	b2Vec2 applyForce({0.f,0.f});
	if (direction.x < 0) {
		applyForce.x = direction.x;
		
	}
	else if(direction.x > 0)
		applyForce.x = direction.x;

	if(direction.y < 0)
		applyForce.y = direction.y;
	else if (direction.y > 0)
		applyForce.y = direction.y;
	
	findBody(entity)->ApplyLinearImpulse(applyForce, findBody(entity)->GetWorldCenter(), true);
}

void PhysicsDevice::applyAngularForce(Entity& entity, bool right)
{
	float forceMultiplier = 1;
	if (!right) forceMultiplier *= -1;
	forceMultiplier = findBody(entity)->GetAngularVelocity() + (forceMultiplier * 2.0f * (1 / 50));
	findBody(entity)->SetAngularVelocity(forceMultiplier);
}

b2Body* PhysicsDevice::findBody(Entity& entity)
{

	for (b2Body* body = world->GetBodyList(); body; body = body->GetNext())
	{
		//when we have a match, return it.
		if (reinterpret_cast<uintptr_t>(&entity) == body->GetUserData().pointer)
		{
			
			return body;
		}
	}
	//if there was no match, return nullptr
	return nullptr;
}

bool PhysicsDevice::removeEntity(Entity& entity)
{
	//Find the body based on the passed object
	b2Body* body = findBody(entity);

	//check to see if we have a body.
	if (body == nullptr)
	{
		return false;
	}
	else
	{
		//delete the body from the world
		world->DestroyBody(body);
		return true;
	}
}

sf::Vector2f PhysicsDevice::PV2GV(b2Vec2 physicsVec)
{
	return { PW2RW(physicsVec.x), PW2RW(physicsVec.y) };
}

b2Vec2 PhysicsDevice::GV2PV(sf::Vector2f physicsVec)
{
	return {RW2PW(physicsVec.x), RW2PW(physicsVec.y) };
}

void PhysicsDevice::setVelocity(Entity& entity, sf::Vector2f velocity)
{
	b2Body* body = findBody(entity);
	body->SetLinearVelocity({ velocity.x /10,velocity.y/10 });
}

sf::Vector2f PhysicsDevice::alignCenters(Entity& entity)
{
	//needed for position in physics world
	b2Vec2 physPosition = findBody(entity)->GetPosition();
	//needed for width/height of object;
	//Texture* texture = object->getComponent<Sprite>()->getTexture();

	//adjust x & y positions by half the sprite's width and heigh respectively to get the top left corner!
	sf::Vector2f position{ PW2RW(physPosition.x) - (SPRITE_WIDTH / 2), PW2RW(physPosition.y) - (SPRITE_HEIGHT / 2) };
	return (position);
}

