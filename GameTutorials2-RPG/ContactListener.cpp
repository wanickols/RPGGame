#include "stdafx.h"
#include "ContactListener.h"
#include "Entity.h"
#include "ComponentInclude.h"

void ContactListener::PreSolve(b2Contact* contact, const b2Manifold* oldManifold)
{
	{

		//Grab the two Physics Bodies involved in the Contact
		b2Body* bodyA = contact->GetFixtureA()->GetBody();
		b2Body* bodyB = contact->GetFixtureB()->GetBody();

		Entity* entityA = reinterpret_cast<Entity*>(bodyA->GetUserData().pointer);
		Entity* entityB = reinterpret_cast<Entity*>(bodyB->GetUserData().pointer);
		//Conduct a modification
		if (bodyA->GetType() == b2_dynamicBody && bodyB->GetType() == b2_dynamicBody) {
			
			entityA->getComponent<physicsComponent>()->collisions(entityB);
			entityB->getComponent<physicsComponent>()->collisions(entityA);

			bodyA->SetLinearVelocity(b2Vec2(RW2PW(-30), RW2PW(-10)));
			bodyB->SetLinearVelocity(b2Vec2(RW2PW(30), RW2PW(30)));




		}

		
	 
	}
}
