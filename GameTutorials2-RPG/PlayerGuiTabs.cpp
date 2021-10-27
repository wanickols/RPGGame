#include "stdafx.h"
#include "PlayerGuiTabs.h"
#include "CharacterTab.h"
#include "Entity.h"

void PlayerGuiTabs::initTabs()
{
	this->tabs.push_back(std::make_unique<CharacterTab>(vm, font, player));
}

void PlayerGuiTabs::initKeyTime()
{
}

PlayerGuiTabs::PlayerGuiTabs(sf::VideoMode& vm, sf::Font& font, std::shared_ptr<Entity> player)
	: vm(vm), font(font), player(player)
{
	this->initTabs();
	this->initKeyTime();
}

PlayerGuiTabs::~PlayerGuiTabs()
{

}

const bool PlayerGuiTabs::getKeyTime()
{
	return false;
}

const bool PlayerGuiTabs::tabsOpen()
{
	//Loop through tabs and check if any are open
	bool open = false;
	for (size_t i = 0; i < this->tabs.size() && !open; i++)
	{
		if (this->tabs[i]->getOpen())
			open = true;
	}

	return open;
}

void PlayerGuiTabs::toggleTab(const int tab_index)
{
	if (tab_index >= 0 || tab_index < this->tabs.size())
		this->tabs[tab_index]->toggle();
}

void PlayerGuiTabs::update()
{
	

	for (auto& i : tabs)
	{
		if (i->getOpen())
			i->update();
	}
}

void PlayerGuiTabs::render(sf::RenderTarget& target)
{
	for (auto& i : tabs)
	{
		if (i->getOpen())
			i->render(target);
	}
}
