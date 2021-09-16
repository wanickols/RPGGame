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

void MainMenuState::initGui()
{

	sf::VideoMode& vm = stateData->GraphicsSettings->resolution;

	//Background
	background.setSize(
		(sf::Vector2f
		(
			(float)window->getSize().x,
			(float)window->getSize().y)
			)
	);

	if (!bgTexture.loadFromFile("Resources/Images/Backgrounds/MainMenuBackground.png")) {
		throw "ERROR::MAIN_MENU_STATE::FAILED_TO_LOAD_BACKGROUND_TEXTURE";
	}
	
	background.setTexture(&bgTexture);

	//Buttons
	float Button_X_allignment = (window->getDefaultView().getCenter().x / 2) - gui::p2pX(5.2f, vm);
	float Button_Y_allignment = (window->getDefaultView().getCenter().y - gui::p2pY(6.94f, vm));

	buttons["GAME_STATE"] = addButton(Button_X_allignment, Button_Y_allignment, "New Game");
	buttons["SETTINGS"] = addButton(Button_X_allignment, Button_Y_allignment + 100, "Settings");
	buttons["EDITOR_STATE"] = addButton(Button_X_allignment, Button_Y_allignment + 200, "Editor");
	buttons["EXIT_STATE"] = addButton(Button_X_allignment, Button_Y_allignment + 300, "Exit");
}

void MainMenuState::initKeybinds()
{
	std::ifstream ifs("Config/MainMenuState_keybinds.ini");

	if (ifs.is_open()) {

		std::string key = "";
		std::string key2 = "";

		while (ifs >> key >> key2) {
			keybinds[key] = supportedKeys->at(key2);
		}

	}

	ifs.close();


}


MainMenuState::MainMenuState(std::shared_ptr<StateData> state_data)
	: State(state_data)
{
	//initVariables();
	initGui();
	initKeybinds();

}

MainMenuState::~MainMenuState()
{
}

void MainMenuState::resetGui()
{
	
	buttons.clear();
	initGui();
}


void MainMenuState::updateInput(const float& dt)
{}

void MainMenuState::updateButtons()
{
	/*Updates all the buttons and their states and handles their functionality*/
	for (auto& it : buttons)
	{
		it.second->update(mousePosView);
	}


		//new game
		if (buttons["GAME_STATE"]->isPressed())
		{
			states->push(std::make_unique<GameState>(stateData));
		}
		//Settings
		if (buttons["SETTINGS"]->isPressed())
		{
			states->push(std::make_unique<SettingsState>(stateData));
		}
		//Editor
		if (buttons["EDITOR_STATE"]->isPressed())
		{
			states->push(std::make_unique<EditorState>(stateData));
		}

		//Quit the game
		if (buttons["EXIT_STATE"]->isPressed())
		{
			endState();
		}
}

void MainMenuState::update(const float& dt)
{
	if (background.getSize().y != window->getSize().y || background.getSize().x != window->getSize().x)
		resetGui();

	updateMousePositions();
	updateInput(dt);

	updateButtons();
	//player.update(dt);



}

void MainMenuState::render(std::shared_ptr<sf::RenderTarget> target)
{
	if (!target)
		target = window;
	//player.render(target);
	target->draw(background);
	renderButtons(*target);
}

void MainMenuState::renderButtons(sf::RenderTarget& target)
{
	for (auto& it : buttons)
	{
		it.second->render(target);
	}
}

