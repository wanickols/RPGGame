#include "stdafx.h"
#include "CharacterTab.h"
#include "Entity.h"
#include "Attribute.h"

void CharacterTab::initText()
{
	//Text
	this->infoText.setFont(this->font);
	this->infoText.setCharacterSize(24);
	this->infoText.setFillColor(sf::Color(200, 200, 200, 240));
	this->infoText.setPosition(back.getPosition().x + 20.f, back.getPosition().y + 20.f);

	this->infoText.setString(player->getComponent<Attribute>()->toStringCharacterTab());
}

CharacterTab::CharacterTab(sf::VideoMode& vm, sf::Font& font, std::shared_ptr<Entity> player)
	: Tab(vm, font, player, false)
{
	//Background
	back.setFillColor(sf::Color(520, 20, 20, 240));
	back.setSize(sf::Vector2f(gui::p2pX(45.f, this->vm), static_cast<float>(this->vm.height)));

	this->initText();
}

CharacterTab::~CharacterTab()
{

}

void CharacterTab::update()
{
	if (!this->hidden)
	{
		//Update the character info
		this->infoText.setString(player->getComponent<Attribute>()->toStringCharacterTab());
	}
}

void CharacterTab::render(sf::RenderTarget& target)
{
	if (!this->hidden)
	{
		target.draw(back);
		target.draw(infoText);
	}
}