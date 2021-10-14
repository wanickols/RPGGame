#include "stdafx.h"
#include "UserInput.h"
#include "Entity.h"
#include "Player.h"
#include "Movement.h"
#include "Rune.h"
#include "AnimationC.h"

UserInput::UserInput(Entity* owner)
	: Component("input", owner)
{
	Player* player = dynamic_cast<Player*>(owner);
	this->player = player;
	attacking = false;
}

void UserInput::shoot(const sf::Vector2f& mousePosView)
{
	attacking = false;
	player->getActiveRune()->shoot(owner->getPosition().x, owner->getPosition().y, owner->getComponent<Movement>()->getVelocity().x + (mousePosView.x - owner->getPosition().x) / 100, owner->getComponent<Movement>()->getVelocity().y + (mousePosView.y - owner->getPosition().y) / 100, owner->getComponent<Movement>()->getLastState());
	
}

void UserInput::update(const float& dt, const sf::Vector2f mousePosView)
{

	if (owner->getComponent<Movement>()->getState(ATTACK)) {
		attacking = true;
		if (attacking) {
			switch (owner->getComponent<Movement>()->getLastState())
			{
			case(DOWNIDLE):
				owner->getComponent<Movement>()->setLastState(DOWNIDLE);
				if (!owner->getComponent<AnimationC>()->getLastIsDone("IDLEATTACKDOWN"))
				{
					if (owner->getComponent<AnimationC>()->play("IDLEATTACKDOWN", dt, false)) {
						shoot(mousePosView);
					}
				}
				else {
					if (!owner->getComponent<AnimationC>()->play("IDLEATTACKINGDOWN", dt, false)) {

					}
					else {
						shoot(mousePosView);
						owner->getComponent<AnimationC>()->setIsDone("IDLEATTACKINGDOWN", false);
					}
				}
				break;
			case(MOVING_DOWN):
				owner->getComponent<Movement>()->setLastState(MOVING_DOWN);
				if (!owner->getComponent<AnimationC>()->play("MOVINGATTACKDOWN", dt, false)) {

				}
				else {
					shoot(mousePosView);
					owner->getComponent<AnimationC>()->setIsDone("MOVINGATTACKDOWN", false);
				}
				break;
			case(UPIDLE):
				owner->getComponent<Movement>()->setLastState(UPIDLE);
				if (!owner->getComponent<AnimationC>()->getLastIsDone("IDLEATTACKUP"))
				{
					if (owner->getComponent<AnimationC>()->play("IDLEATTACKUP", dt, false)) {
						shoot(mousePosView);
					}
				}
				else {
					if (!owner->getComponent<AnimationC>()->play("IDLEATTACKINGUP", dt, false)) {

					}
					else {

						shoot(mousePosView);
						owner->getComponent<AnimationC>()->setIsDone("IDLEATTACKINGUP", false);
					}
				}
				break;
			case(MOVING_UP):
				owner->getComponent<Movement>()->setLastState(MOVING_UP);
				if (!owner->getComponent<AnimationC>()->play("MOVINGATTACKUP", dt, false)) {

				}
				else {
					shoot(mousePosView);
					owner->getComponent<AnimationC>()->setIsDone("MOVINGATTACKUP", false);

				}
				break;
			case(RIGHTIDLE):
				owner->getComponent<Movement>()->setLastState(RIGHTIDLE);
				if (!owner->getComponent<AnimationC>()->getLastIsDone("IDLEATTACKRIGHT"))
				{
					if (owner->getComponent<AnimationC>()->play("IDLEATTACKRIGHT", dt, false)) {
						shoot(mousePosView);
					}
				}
				else {
					if (!owner->getComponent<AnimationC>()->play("IDLEATTACKINGRIGHT", dt, false)) {
					}
					else {
						shoot(mousePosView);
						owner->getComponent<AnimationC>()->setIsDone("IDLEATTACKINGRIGHT", false);
					}
				}
				break;
			case(MOVING_RIGHT):
				owner->getComponent<Movement>()->setLastState(MOVING_RIGHT);
				if (!owner->getComponent<AnimationC>()->play("MOVINGATTACKRIGHT", dt, false)) {

				}
				else {
					shoot(mousePosView);
					owner->getComponent<AnimationC>()->setIsDone("MOVINGATTACKRIGHT", false);

				}

				break;
			case(LEFTIDLE):
				owner->getComponent<Movement>()->setLastState(LEFTIDLE);
				if (!owner->getComponent<AnimationC>()->getLastIsDone("IDLEATTACKLEFT"))
				{
					if (owner->getComponent<AnimationC>()->play("IDLEATTACKLEFT", dt, false)) {
						shoot(mousePosView);
					}
				}
				else {
					if (!owner->getComponent<AnimationC>()->play("IDLEATTACKINGLEFT", dt, false)) {
					}
					else {
						shoot(mousePosView);
						owner->getComponent<AnimationC>()->setIsDone("IDLEATTACKINGLEFT", false);
					}
				}
				break;
			case(MOVING_LEFT):
				owner->getComponent<Movement>()->setLastState(MOVING_LEFT);
				if (!owner->getComponent<AnimationC>()->play("MOVINGATTACKLEFT", dt, false)) {

				}
				else {
					shoot(mousePosView);
					owner->getComponent<AnimationC>()->setIsDone("MOVINGATTACKLEFT", false);
				}
				break;

			}
		}
		owner->getComponent<Movement>()->getState();
	}
	else {
		//ANIMATIONS WHILE NOT ATTACKING
		switch (owner->getComponent<Movement>()->getState())
		{
		case(DOWNIDLE):
			owner->getComponent<AnimationC>()->play("DOWNIDLE", dt, false);
			break;
		case(UPIDLE):
			owner->getComponent<AnimationC>()->play("UPIDLE", dt, false);
			break;
		case(LEFTIDLE):
			owner->getComponent<AnimationC>()->play("LEFTIDLE", dt, false);
			break;
		case(RIGHTIDLE):
			owner->getComponent<AnimationC>()->play("RIGHTIDLE", dt, false);
			break;
		case(MOVING_LEFT):
			owner->getComponent<AnimationC>()->play("WALK_LEFT", dt, owner->getComponent<Movement>()->getVelocity().x, owner->getComponent<Movement>()->getMaxVelocity(), false);
			break;
		case(MOVING_RIGHT):
			owner->getComponent<AnimationC>()->play("WALK_RIGHT", dt, owner->getComponent<Movement>()->getVelocity().x, owner->getComponent<Movement>()->getMaxVelocity(), false);
			break;
		case(MOVING_UP):
			owner->getComponent<AnimationC>()->play("WALK_UP", dt, owner->getComponent<Movement>()->getVelocity().y, owner->getComponent<Movement>()->getMaxVelocity(), false);
			break;
		case(MOVING_DOWN):
			owner->getComponent<AnimationC>()->play("WALK_DOWN", dt, owner->getComponent<Movement>()->getVelocity().y, owner->getComponent<Movement>()->getMaxVelocity(), false);
			break;
		}
	}
}
