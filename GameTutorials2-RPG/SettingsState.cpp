#include "stdafx.h"
#include "SettingsState.h"
#include "MainMenuState.h"
#include "GraphicsSettings.h"


void SettingsState::initVariables()
{
	this->modes = sf::VideoMode::getFullscreenModes();
}

void SettingsState::initKeybinds()
{
	std::ifstream ifs("Config/mainmenustate_keybinds.ini");

	if (ifs.is_open())
	{
		std::string key = "";
		std::string key2 = "";

		while (ifs >> key >> key2)
		{
			this->keybinds[key] = this->supportedKeys->at(key2);
		}
	}

	ifs.close();
}

void SettingsState::initGui()
{

	sf::VideoMode& vm = this->stateData->GraphicsSettings->resolution;


	//Button Init
	this->buttons["EXIT"] = this->addButton(gui::p2pX(78.1f, vm), gui::p2pY(83.f, vm), "Back", gui::p2pX(13.f, vm), gui::p2pY(7.f, vm));
	this->buttons["APPLY"] = this->addButton(gui::p2pX(46.f, vm), gui::p2pY(83.f, vm), "Apply", gui::p2pX(26.f, vm), gui::p2pY(7.f, vm));
	this->buttons["APPLY"]->setBackgroundColor(sf::Color(100, 100, 100, 50), sf::Color(150, 150, 150, 100), sf::Color(20, 20, 20, 20));
	std::vector<std::string> modes_str;
	for (auto& i : this->modes)
	{
		modes_str.push_back(std::to_string(i.width) + 'x' + std::to_string(i.height));
	}
	

	//DropDownList init
	this->dropDownLists["RESOLUTION"] = std::make_unique<gui::DropDownList>(gui::p2pX(23.f, vm), gui::p2pY(41.6f, vm), gui::p2pX(10.4f, vm), gui::p2pY(4.6f, vm), font, modes_str.data(), modes_str.size(), GraphicsSettings->currMode);

	//Text Init
	this->optionsText.setFont(this->font);

	this->optionsText.setPosition(gui::p2pX(12.f, vm), gui::p2pY(41.f, vm));
	this->optionsText.setCharacterSize((unsigned int)gui::p2pX(2.6f, vm));
	this->optionsText.setFillColor(sf::Color(255, 255, 255, 200));


	this->optionsText.setString(
		"Resolution \n\nFullscreen \n\nVsync \n\nAntialiasing");
}

void SettingsState::resetGui()
{
	this->dropDownLists.clear();
	this->buttons.clear();
	this->initGui();
}


SettingsState::SettingsState(std::shared_ptr<StateData>  state_data)
	: State(state_data)
{
	this->initVariables();
	this->initKeybinds();
	this->initGui();
}

SettingsState::~SettingsState()
{

}

void SettingsState::updateInput(const float& dt)
{

}

void SettingsState::updateGui(const float& dt)
{
	//Updates all gui elements
	//Buttons
	for (auto& it : this->buttons)
	{
		it.second->update(this->mousePosView);
	}

	if (this->buttons["EXIT"]->isPressed())
	{
		this->endState();
	}

	if (this->buttons["APPLY"]->isPressed())
	{
		//TEST REMOVE LATER <==================

		GraphicsSettings->currMode = this->dropDownLists["RESOLUTION"]->getActiveID();
		this->GraphicsSettings->resolution = this->modes[GraphicsSettings->currMode];
		this->window->create(this->GraphicsSettings->resolution, this->GraphicsSettings->title, sf::Style::Default);
		this->resetGui();
		GraphicsSettings->saveToFile("Config/graphics.ini");
	}

	//DropDownList
	for (auto& it2 : this->dropDownLists)
	{
		it2.second->update(this->mousePosView, dt);
	}
}

void SettingsState::update(const float& dt)
{
	this->updateMousePositions();
	this->updateInput(dt);
	this->updateGui(dt);
}

void SettingsState::renderGui(sf::RenderTarget& target)
{
	for (auto& it : this->buttons)
	{
		it.second->render(target);
	}

	for (auto& it : this->dropDownLists)
	{
		it.second->render(target);
	}
}

void SettingsState::render(std::shared_ptr<sf::RenderTarget> target)
{
	if (!target)
		target = this->window;

	target->draw(this->background);


	this->renderGui(*target);

	target->draw(this->optionsText);
}