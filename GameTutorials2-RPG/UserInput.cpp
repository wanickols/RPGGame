#include "stdafx.h"
#include "UserInput.h"
#include "Entity.h"
#include "Player.h"
#include "Movement.h"
#include "RuneComponent.h"
#include "Rune.h"
#include "AnimationC.h"
#include "physicsComponent.h"
#include "PhysicsDevice.h"

UserInput::UserInput(Entity& owner)
	: Component("input", owner)
{
	Player* player = dynamic_cast<Player*>(&owner);
	this->player = player;
	attacking = false;

	movement = owner.getComponent<Movement>();
	animation = owner.getComponent<AnimationC>();
	body = nullptr;
}

void UserInput::shoot(const sf::Vector2f& mousePosView)
{
	if (keytimer.getKeyTime()) {
		attacking = false;
		sf::Vector2f position = owner.getComponent<physicsComponent>()->pDevice->getPosition(owner);
		sf::Vector2f offset = owner.getComponent<physicsComponent>()->getOffset();
		player->getActiveRune()->getItemComponent<RuneComponent>()->shoot(position.x, position.y - offset.y - 50, body->GetLinearVelocity().x + (mousePosView.x - position.x) / 100, body->GetLinearVelocity().y + (mousePosView.y - position.y) / 100, movement->getDirection(), owner.getComponent<physicsComponent>()->pDevice);
	}
}

void UserInput::update(const float& dt, const sf::Vector2f mousePosView)
{
	keytimer.updateKeyTime(dt);
	if(body == nullptr)
		body = owner.getComponent<physicsComponent>()->pDevice->findBody(owner);



	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)){
		attacking = true;
		if (attacking) {
			if(movement->getMOVING())
			{
				switch (movement->getDirection())
				{
				case(facing::LEFT):
					if (!animation->play("MOVINGATTACKLEFT", dt, false)) {

					}
					else {
						shoot(mousePosView);
						animation->setIsDone("MOVINGATTACKLEFT", false);
					}
					break;
				case(facing::RIGHT):
					if (!animation->play("MOVINGATTACKRIGHT", dt, false)) {

					}
					else {
						shoot(mousePosView);
						animation->setIsDone("MOVINGATTACKRIGHT", false);

					}
					break;
				case(facing::UP):
					if (!animation->play("MOVINGATTACKUP", dt, false)) {

					}
					else {
						shoot(mousePosView);
						animation->setIsDone("MOVINGATTACKUP", false);

					}
					break;
				case(facing::DOWN):
					if (!animation->play("MOVINGATTACKDOWN", dt, false)) {

					}
					else {
						shoot(mousePosView);
						animation->setIsDone("MOVINGATTACKDOWN", false);
					}
					break;
				}
			
			}
			else
			{
				switch (movement->getDirection())
				{
				case(facing::LEFT):
						if (!animation->play("IDLEATTACKINGLEFT", dt, false)) {
						}
						else {
							shoot(mousePosView);
							animation->setIsDone("IDLEATTACKINGLEFT", false);
						}
					break;
				case(facing::RIGHT):
						if (!animation->play("IDLEATTACKINGRIGHT", dt, false)) {
						}
						else {
							shoot(mousePosView);
							animation->setIsDone("IDLEATTACKINGRIGHT", false);
						}
					break;
				case(facing::UP):
						if (!animation->play("IDLEATTACKINGUP", dt, false)) {

						}
						else {

							shoot(mousePosView);
							animation->setIsDone("IDLEATTACKINGUP", false);
						}
					break;
				case(facing::DOWN):
						if (!animation->play("IDLEATTACKINGDOWN", dt, false)) {

						}
						else {
							shoot(mousePosView);
							animation->setIsDone("IDLEATTACKINGDOWN", false);
						}
					break;
					}
				}
			}
	}
	else {
		if (movement->getMOVING()) {
			switch (movement->getDirection())
			{
			case(facing::LEFT):
				animation->play("WALKLEFT", dt, body->GetLinearVelocity().x, movement->getMaxVelocity().x, false);
				break;
			case(facing::RIGHT):
				animation->play("WALKRIGHT", dt, body->GetLinearVelocity().x, movement->getMaxVelocity().x, false);
				break;
			case(facing::UP):
				animation->play("WALKUP", dt, body->GetLinearVelocity().y, movement->getMaxVelocity().y, false);
				break;
			case(facing::DOWN):
				animation->play("WALKDOWN", dt, body->GetLinearVelocity().y, movement->getMaxVelocity().y, false);
				break;
			}
		}else
		{
			switch (movement->getDirection())
			{
			case(facing::UP):
				animation->play("UPIDLE", dt, false);
				break;
			case(facing::DOWN):
				animation->play("DOWNIDLE", dt, false);
				break;
			case(facing::LEFT):
				animation->play("LEFTIDLE", dt, false);
				break;
			case(facing::RIGHT):
				animation->play("RIGHTIDLE", dt, false);
				break;
			}
		}
	}
}

void UserInput::handleInput(std::map<std::string, int>& keybinds, const float& dt)
{

		//Player input
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("Move_Up")))) {
			movement->setDirection(facing::UP);
			movement->move(0.f, -1.f, dt);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("Move_Left")))) {
			movement->setDirection(facing::LEFT);
			movement->move(-1.f, 0.f, dt);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("Move_Down")))) {
			movement->setDirection(facing::DOWN);
			movement->move(0.f, 1.f, dt);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("Move_Right")))) {
			movement->setDirection(facing::RIGHT);
			movement->move(1.f, 0.f, dt);

		}
}
