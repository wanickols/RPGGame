#include "stdafx.h"
#include "InputComponent.h"
#include "Entity.h"
#include "Player.h"
#include "MovementComponent.h"
#include "Rune.h"
#include "AnimationComponent.h"

InputComponent::InputComponent(Entity* owner)
	: Component("input", owner)
{
	Player* player = dynamic_cast<Player*>(owner);
	this->player = player;
	attacking = false;
}

void InputComponent::shoot(const sf::Vector2f& mousePosView)
{
	attacking = false;
	player->getActiveRune()->shoot(owner->getPosition().x, owner->getPosition().y, owner->getComponent<MovementComponent>()->getVelocity().x + (mousePosView.x - owner->getPosition().x) / 100, owner->getComponent<MovementComponent>()->getVelocity().y + (mousePosView.y - owner->getPosition().y) / 100, owner->getComponent<MovementComponent>()->getLastState());
	
}

void InputComponent::update(const float& dt, const sf::Vector2f mousePosView)
{

	if (owner->getComponent<MovementComponent>()->getState(ATTACK)) {
		attacking = true;
		if (attacking) {
			switch (owner->getComponent<MovementComponent>()->getLastState())
			{
			case(DOWNIDLE):
				owner->getComponent<MovementComponent>()->setLastState(DOWNIDLE);
				if (!owner->getComponent<AnimationComponent>()->getLastIsDone("IDLEATTACKDOWN"))
				{
					if (owner->getComponent<AnimationComponent>()->play("IDLEATTACKDOWN", dt, false)) {
						shoot(mousePosView);
					}
				}
				else {
					if (!owner->getComponent<AnimationComponent>()->play("IDLEATTACKINGDOWN", dt, false)) {

					}
					else {
						shoot(mousePosView);
						owner->getComponent<AnimationComponent>()->setIsDone("IDLEATTACKINGDOWN", false);
					}
				}
				break;
			case(MOVING_DOWN):
				owner->getComponent<MovementComponent>()->setLastState(MOVING_DOWN);
				if (!owner->getComponent<AnimationComponent>()->play("MOVINGATTACKDOWN", dt, false)) {

				}
				else {
					shoot(mousePosView);
					owner->getComponent<AnimationComponent>()->setIsDone("MOVINGATTACKDOWN", false);
				}
				break;
			case(UPIDLE):
				owner->getComponent<MovementComponent>()->setLastState(UPIDLE);
				if (!owner->getComponent<AnimationComponent>()->getLastIsDone("IDLEATTACKUP"))
				{
					if (owner->getComponent<AnimationComponent>()->play("IDLEATTACKUP", dt, false)) {
						shoot(mousePosView);
					}
				}
				else {
					if (!owner->getComponent<AnimationComponent>()->play("IDLEATTACKINGUP", dt, false)) {

					}
					else {

						shoot(mousePosView);
						owner->getComponent<AnimationComponent>()->setIsDone("IDLEATTACKINGUP", false);
					}
				}
				break;
			case(MOVING_UP):
				owner->getComponent<MovementComponent>()->setLastState(MOVING_UP);
				if (!owner->getComponent<AnimationComponent>()->play("MOVINGATTACKUP", dt, false)) {

				}
				else {
					shoot(mousePosView);
					owner->getComponent<AnimationComponent>()->setIsDone("MOVINGATTACKUP", false);

				}
				break;
			case(RIGHTIDLE):
				owner->getComponent<MovementComponent>()->setLastState(RIGHTIDLE);
				if (!owner->getComponent<AnimationComponent>()->getLastIsDone("IDLEATTACKRIGHT"))
				{
					if (owner->getComponent<AnimationComponent>()->play("IDLEATTACKRIGHT", dt, false)) {
						shoot(mousePosView);
					}
				}
				else {
					if (!owner->getComponent<AnimationComponent>()->play("IDLEATTACKINGRIGHT", dt, false)) {
					}
					else {
						shoot(mousePosView);
						owner->getComponent<AnimationComponent>()->setIsDone("IDLEATTACKINGRIGHT", false);
					}
				}
				break;
			case(MOVING_RIGHT):
				owner->getComponent<MovementComponent>()->setLastState(MOVING_RIGHT);
				if (!owner->getComponent<AnimationComponent>()->play("MOVINGATTACKRIGHT", dt, false)) {

				}
				else {
					shoot(mousePosView);
					owner->getComponent<AnimationComponent>()->setIsDone("MOVINGATTACKRIGHT", false);

				}

				break;
			case(LEFTIDLE):
				owner->getComponent<MovementComponent>()->setLastState(LEFTIDLE);
				if (!owner->getComponent<AnimationComponent>()->getLastIsDone("IDLEATTACKLEFT"))
				{
					if (owner->getComponent<AnimationComponent>()->play("IDLEATTACKLEFT", dt, false)) {
						shoot(mousePosView);
					}
				}
				else {
					if (!owner->getComponent<AnimationComponent>()->play("IDLEATTACKINGLEFT", dt, false)) {
					}
					else {
						shoot(mousePosView);
						owner->getComponent<AnimationComponent>()->setIsDone("IDLEATTACKINGLEFT", false);
					}
				}
				break;
			case(MOVING_LEFT):
				owner->getComponent<MovementComponent>()->setLastState(MOVING_LEFT);
				if (!owner->getComponent<AnimationComponent>()->play("MOVINGATTACKLEFT", dt, false)) {

				}
				else {
					shoot(mousePosView);
					owner->getComponent<AnimationComponent>()->setIsDone("MOVINGATTACKLEFT", false);
				}
				break;

			}
		}
		owner->getComponent<MovementComponent>()->getState();
	}
	else {
		//ANIMATIONS WHILE NOT ATTACKING
		switch (owner->getComponent<MovementComponent>()->getState())
		{
		case(DOWNIDLE):
			owner->getComponent<AnimationComponent>()->play("DOWNIDLE", dt, false);
			break;
		case(UPIDLE):
			owner->getComponent<AnimationComponent>()->play("UPIDLE", dt, false);
			break;
		case(LEFTIDLE):
			owner->getComponent<AnimationComponent>()->play("LEFTIDLE", dt, false);
			break;
		case(RIGHTIDLE):
			owner->getComponent<AnimationComponent>()->play("RIGHTIDLE", dt, false);
			break;
		case(MOVING_LEFT):
			owner->getComponent<AnimationComponent>()->play("WALK_LEFT", dt, owner->getComponent<MovementComponent>()->getVelocity().x, owner->getComponent<MovementComponent>()->getMaxVelocity(), false);
			break;
		case(MOVING_RIGHT):
			owner->getComponent<AnimationComponent>()->play("WALK_RIGHT", dt, owner->getComponent<MovementComponent>()->getVelocity().x, owner->getComponent<MovementComponent>()->getMaxVelocity(), false);
			break;
		case(MOVING_UP):
			owner->getComponent<AnimationComponent>()->play("WALK_UP", dt, owner->getComponent<MovementComponent>()->getVelocity().y, owner->getComponent<MovementComponent>()->getMaxVelocity(), false);
			break;
		case(MOVING_DOWN):
			owner->getComponent<AnimationComponent>()->play("WALK_DOWN", dt, owner->getComponent<MovementComponent>()->getVelocity().y, owner->getComponent<MovementComponent>()->getMaxVelocity(), false);
			break;
		}
	}
}
