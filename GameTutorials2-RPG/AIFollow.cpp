#include "stdafx.h"
#include "Movement.h"
#include "AnimationC.h"
#include "enemyAi.h"
#include "Combat.h"
#include "PhysicsDevice.h"
#include "physicsComponent.h"
#include "AIFollow.h"
#include "Entity.h"


AIFollow::AIFollow(std::shared_ptr<Entity> entity, Entity& owner)
	: AISetting("Follow", entity, owner)
{
	keytimer.keyTimeMax = 150.f;
	
}

void AIFollow::update(const float& dt)
{
	if (updateMe) {
		keytimer.updateKeyTime(dt);
		reaction(dt);
	}
}

void AIFollow::reaction(const float& dt)
{
	const sf::Vector2f& enitityPos = entity->getCenterPosition();
	const sf::Vector2f& ownerPos = owner.getCenterPosition();

	b2Vec2 velocity = owner.getbVectorDistance(enitityPos);
	if (owner.getDistance(enitityPos) > 100) {
		movement->setMOVING(true);
		if (abs(enitityPos.x - ownerPos.x) > abs(enitityPos.y - ownerPos.y)) {
			if (enitityPos.x > ownerPos.x)
				movement->setDirection(facing::RIGHT);
			else if (entity->getPosition().x < owner.getPosition().x)
				movement->setDirection(facing::LEFT);
		}
		else
		{
			if (enitityPos.y > ownerPos.y)
				movement->setDirection(facing::DOWN);
			else if (enitityPos.y < ownerPos.y)
				movement->setDirection(facing::UP);
		}
	}
	else
	{
		//Attack
		if (keytimer.getKeyTime()) {
			b2Body* body = owner.getComponent<physicsComponent>()->pDevice->findBody(owner);
			float force = 3.f;
			body->ApplyLinearImpulseToCenter(b2Vec2({ velocity.x * force, velocity.y * force }), true);
		}
		movement->setMOVING(false);
		owner.getComponent<enemyAi>()->setWalkSpeed(0.f);

	}
}
