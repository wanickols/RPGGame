#include "stdafx.h"
#include "PhysicsDevice.h"
#include "Entity.h"
#include "AnimationC.h"

PhysicsDevice::PhysicsDevice(sf::Vector2f gravity)
{
}

//**************************************
//Creates a new world on initialization
bool PhysicsDevice::initialize()
//**************************************
{
	world = std::make_shared<b2World>(gravity);
	if (world == nullptr) return false;
	return true;
}

//**************************************
//Steps the physics world
//
bool PhysicsDevice::update(float dt)
//**************************************
{
	// 8 3 accepted good values, can play later maybe
	world->Step(dt, 8, 3);
	return true;
}


bool PhysicsDevice::createFixture(std::shared_ptr<Entity> entity, GAME_PHYSICS& physics)
{
	//need the sprite component first!
	if (entity->getComponent<AnimationC>() == nullptr) return false;
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

	//divides by 2 to center it
	sf::Vector2f position{ entity->getComponent<AnimationC>()->getSprite().getGlobalBounds().left / 2, entity->getComponent<AnimationC>()->getSprite().getGlobalBounds().top / 2 };

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

	//Set fixture's shape
	switch (physics.objectShape)
	{
	case GAME_RECTANGLE:
		//rectangle's dimensions
		pShape.SetAsBox(RW2PW(position.x), RW2PW(position.y));
		shapefd.shape = &pShape;
		break;
	case GAME_CIRCLE:
		//circle radius based on object's width.
		float width = entity->getComponent<AnimationC>()->getSprite().getGlobalBounds().width / 2.0f;
		float height = entity->getComponent<AnimationC>()->getSprite().getGlobalBounds().height / 2.0f;

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

sf::Vector2f PhysicsDevice::getPosition(std::shared_ptr<Entity> entity)
{
	return(alignCenters(entity));
}

float PhysicsDevice::getAngle(std::shared_ptr<Entity> entity)
{
	return (PW2RWAngle(findBody(entity)->GetAngle()));
}

void PhysicsDevice::applyForce(std::shared_ptr<Entity> entity, bool forward)
{
	int forceMultiplier = 10;
	b2Vec2 applyForce;
	if (forward)
	{
		applyForce.x = (cosf(getAngle(entity) * PI / 180) - (PI / 2)) * forceMultiplier;
		applyForce.y = (sinf(getAngle(entity) * PI / 180) - (PI / 2)) * forceMultiplier;
	}
	else
	{
		applyForce.x = (cosf(getAngle(entity) * PI / 180) + (PI / 2)) * forceMultiplier;
		applyForce.y = (sinf(getAngle(entity) * PI / 180) + (PI / 2)) * forceMultiplier;
	}
	findBody(entity)->ApplyLinearImpulse(applyForce, findBody(entity)->GetWorldCenter(), true);
}

void PhysicsDevice::applyAngularForce(std::shared_ptr<Entity> entity, bool right)
{
	float forceMultiplier = 1;
	if (!right) forceMultiplier *= -1;
	forceMultiplier = findBody(entity)->GetAngularVelocity() + (forceMultiplier * 2.0f * (1 / 50));
	findBody(entity)->SetAngularVelocity(forceMultiplier);
}

b2Body* PhysicsDevice::findBody(std::shared_ptr<Entity> entity)
{
	for (b2Body* body = world->GetBodyList(); body; body = body->GetNext())
	{
		//when we have a match, return it.
		if ((b2BodyUserData*)entity.get() == &body->GetUserData())
		{
			return body;
		}
	}
	//if there was no match, return nullptr
	return nullptr;
}

bool PhysicsDevice::removeEntity(std::shared_ptr<Entity> entity)
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

sf::Vector2f PhysicsDevice::alignCenters(std::shared_ptr<Entity> entity)
{
	//needed for position in physics world
	b2Vec2 physPosition = findBody(entity)->GetPosition();
	//needed for width/height of object;
	//Texture* texture = object->getComponent<Sprite>()->getTexture();

	//adjust x & y positions by half the sprite's width and heigh respectively to get the top left corner!
	sf::Vector2f position{ PW2RW(physPosition.x) - (SPRITE_WIDTH / 2), PW2RW(physPosition.y) - (SPRITE_HEIGHT / 2) };
	return (position);
}

