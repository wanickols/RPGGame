#include "stdafx.h"
#include "enemyGui.h"
#include "Entity.h"
#include "Attribute.h"
#include "Hitbox.h"
enemyGui::enemyGui(Entity* owner, sf::Font& font, sf::VideoMode& vm)
	: Component("enemyGui", owner), font(font), vm(vm), hidden(true)
{
	width = owner->getComponent<Hitbox>()->getGlobalBounds().width * 2;
	height = owner->getComponent<Hitbox>()->getGlobalBounds().height/3 ;
	healthBar = std::make_unique<gui::progressBar>(width, width, height, owner->getPosition().x, owner->getPosition().y, sf::Color(50, 50, 50, 200), sf::Color(250, 20, 20, 210), this->owner, font, vm, 0, 12, false);
}

void enemyGui::update(const float& dt, const sf::Vector2f mousePosView)
{
	tempPercent = (float)owner->getComponent<Attribute>()->hp / (float)(owner->getComponent<Attribute>()->hpMax);
	healthBar->setPosition(owner->getPosition().x - width/4, owner->getPosition().y);
	healthBar->update(dt, tempPercent);
}

void enemyGui::render(sf::RenderTarget& target, sf::Shader* shader, sf::Vector2f light_position, const bool show_hitbox)
{
	if(!hidden)
		healthBar->render(target);
}

void enemyGui::setHidden(bool hidden)
{
	this->hidden = hidden;
}