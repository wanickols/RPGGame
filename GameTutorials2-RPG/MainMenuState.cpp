#include "stdafx.h"
#include "MainMenuState.h"
#include "GameState.h"
#include "GraphicsSettings.h"
#include "EditorState.h"
#include "SettingsState.h"

//Initializer functions
void MainMenuState::initVariables()
{
}

void MainMenuState::initBackround()
{
	this->background.setSize(
		(sf::Vector2f
		(
			(float)this->window->getSize().x,
			(float)this->window->getSize().y)
			)
	);

	if (!this->bgTexture.loadFromFile("Resources/Images/Backgrounds/MainMenuBackground.png")) {
		throw "ERROR::MAIN_MENU_STATE::FAILED_TO_LOAD_BACKGROUND_TEXTURE";
	}

	this->background.setTexture(&this->bgTexture);
}

void MainMenuState::initKeybinds()
{
	std::ifstream ifs("Config/MainMenuState_keybinds.ini");

	if (ifs.is_open()) {

		std::string key = "";
		std::string key2 = "";

		while (ifs >> key >> key2) {
			this->keybinds[key] = this->supportedKeys->at(key2);
		}

	}

	ifs.close();


}

void MainMenuState::initButtons()
{
	float Button_X_allignment = (this->window->getDefaultView().getCenter().x / 2) - 75;
	float Button_Y_allignment = (this->window->getDefaultView().getCenter().y - 75);

	this->buttons["GAME_STATE"] = this->addButton(Button_X_allignment, Button_Y_allignment, "New Game");
	this->buttons["SETTINGS"] = this->addButton(Button_X_allignment, Button_Y_allignment + 100, "Settings");
	this->buttons["EDITOR_STATE"] = this->addButton(Button_X_allignment, Button_Y_allignment + 200, "Editor");
	this->buttons["EXIT_STATE"] = this->addButton(Button_X_allignment, Button_Y_allignment + 300, "Exit");
}

MainMenuState::MainMenuState(std::shared_ptr<StateData> state_data)
	: State(state_data)
{
	this->initVariables();
	this->initBackround();
	this->initKeybinds();
	this->initButtons();

}

MainMenuState::~MainMenuState()
{
}

void MainMenuState::updateInput(const float& dt)
{}

void MainMenuState::updateButtons()
{
	/*Updates all the buttons and their states and handles their functionality*/
	for (auto& it : this->buttons)
	{
		it.second->update(this->mousePosView);
	}

	//new game
	if (this->buttons["GAME_STATE"]->isPressed())
	{
		this->states->push(std::make_unique<GameState>(this->stateData));
	}
	//Settings
	if (this->buttons["SETTINGS"]->isPressed())
	{
		this->states->push(std::make_unique<SettingsState>(this->stateData));
	}
	//Editor
	if (this->buttons["EDITOR_STATE"]->isPressed())
	{
		this->states->push(std::make_unique<EditorState>(this->stateData));
	}

	//Quit the game
	if (this->buttons["EXIT_STATE"]->isPressed())
	{
		this->endState();
	}
}

void MainMenuState::update(const float& dt)
{
	this->updateMousePositions();
	this->updateInput(dt);

	this->updateButtons();
	//this->player.update(dt);


}

void MainMenuState::render(std::shared_ptr<sf::RenderTarget> target)
{
	if (!target)
		target = this->window;
	//this->player.render(target);
	target->draw(this->background);
	this->renderButtons(*target);
}

void MainMenuState::renderButtons(sf::RenderTarget& target)
{
	for (auto& it : this->buttons)
	{
		it.second->render(target);
	}
}