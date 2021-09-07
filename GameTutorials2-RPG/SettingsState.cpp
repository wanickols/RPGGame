#include "stdafx.h"
#include "SettingsState.h"
#include "MainMenuState.h"
#include "GraphicsSettings.h"


void SettingsState::initVariables()
{
	modes = sf::VideoMode::getFullscreenModes();
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
			keybinds[key] = supportedKeys->at(key2);
		}
	}

	ifs.close();
}

void SettingsState::initGui()
{

	sf::VideoMode& vm = stateData->GraphicsSettings->resolution;


	//Button Init
	buttons["EXIT"] = addButton(gui::p2pX(78.1f, vm), gui::p2pY(83.f, vm), "Back", gui::p2pX(13.f, vm), gui::p2pY(7.f, vm));
	buttons["APPLY"] = addButton(gui::p2pX(46.f, vm), gui::p2pY(83.f, vm), "Apply", gui::p2pX(26.f, vm), gui::p2pY(7.f, vm));
	buttons["APPLY"]->setBackgroundColor(sf::Color(100, 100, 100, 50), sf::Color(150, 150, 150, 100), sf::Color(20, 20, 20, 20));
	std::vector<std::string> modes_str;
	for (auto& i : modes)
	{
		modes_str.push_back(std::to_string(i.width) + 'x' + std::to_string(i.height));
	}
	

	//DropDownList init
	dropDownLists["RESOLUTION"] = std::make_unique<gui::DropDownList>(gui::p2pX(23.f, vm), gui::p2pY(41.6f, vm), gui::p2pX(10.4f, vm), gui::p2pY(4.6f, vm), font, modes_str.data(), modes_str.size(), GraphicsSettings->currMode);

	//Text Init
	optionsText.setFont(font);

	optionsText.setPosition(gui::p2pX(12.f, vm), gui::p2pY(41.f, vm));
	optionsText.setCharacterSize((unsigned int)gui::p2pX(2.6f, vm));
	optionsText.setFillColor(sf::Color(255, 255, 255, 200));


	optionsText.setString(
		"Resolution \n\nFullscreen \n\nVsync \n\nAntialiasing");
}

void SettingsState::resetGui()
{
	dropDownLists.clear();
	buttons.clear();
	initGui();
}


SettingsState::SettingsState(std::shared_ptr<StateData>  state_data)
	: State(state_data)
{
	initVariables();
	initKeybinds();
	initGui();
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
	for (auto& it : buttons)
	{
		it.second->update(mousePosView);
	}

	if (buttons["EXIT"]->isPressed())
	{
		endState();
	}

	if (buttons["APPLY"]->isPressed())
	{
		//TEST REMOVE LATER <==================

		GraphicsSettings->currMode = dropDownLists["RESOLUTION"]->getActiveID();
		GraphicsSettings->resolution = modes[GraphicsSettings->currMode];
		window->create(GraphicsSettings->resolution, GraphicsSettings->title, sf::Style::Default);
		resetGui();
		GraphicsSettings->saveToFile("Config/graphics.ini");
	}

	//DropDownList
	for (auto& it2 : dropDownLists)
	{
		it2.second->update(mousePosView, dt);
	}
}

void SettingsState::update(const float& dt)
{
	updateMousePositions();
	updateInput(dt);
	updateGui(dt);
}

void SettingsState::renderGui(sf::RenderTarget& target)
{
	for (auto& it : buttons)
	{
		it.second->render(target);
	}

	for (auto& it : dropDownLists)
	{
		it.second->render(target);
	}
}

void SettingsState::render(std::shared_ptr<sf::RenderTarget> target)
{
	if (!target)
		target = window;

	target->draw(background);


	renderGui(*target);

	target->draw(optionsText);
}