#include "stdafx.h"
#include "SettingsState.h"
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
	//Button Init

	this->buttons["EXIT"] = this->addButton(1500.f, 900.f, "Back", 250.f, 75.f);
	this->buttons["APPLY"] = this->addButton(this->window->getView().getCenter().x - 250.f, 900.f, "Apply", 500.f, 75.f);
	this->buttons["APPLY"]->setBackgroundColor(sf::Color(100, 100, 100, 50), sf::Color(150, 150, 150, 100), sf::Color(20, 20, 20, 20));
	std::vector<std::string> modes_str;
	for (auto& i : this->modes)
	{
		modes_str.push_back(std::to_string(i.width) + 'x' + std::to_string(i.height));
	}


	//DropDownList init
	this->dropDownLists["RESOLUTION"] = std::make_unique<gui::DropDownList>(450.f, 450.f, 200.f, 50.f, font, modes_str.data(), modes_str.size(), gfxSettings->currMode);
}

void SettingsState::initText()
{
	this->optionsText.setFont(this->font);

	this->optionsText.setPosition(250.f, 450.f);
	this->optionsText.setCharacterSize(50);
	this->optionsText.setFillColor(sf::Color(255, 255, 255, 200));


	this->optionsText.setString(
		"Resolution \n\nFullscreen \n\nVsync \n\nAntialiasing");
}

SettingsState::SettingsState(std::shared_ptr<StateData>  state_data)
	: State(state_data)
{
	this->initVariables();
	this->initKeybinds();
	this->initGui();
	this->initText();
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

		gfxSettings->currMode = this->dropDownLists["RESOLUTION"]->getActiveID();
		this->gfxSettings->resolution = this->modes[gfxSettings->currMode];
		this->window->create(this->gfxSettings->resolution, this->gfxSettings->title, sf::Style::Default);

		gfxSettings->saveToFile("Config/graphics.ini");
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