#include "stdafx.h"
#include "Game.h"
#include "MainMenuState.h"
#include "GraphicsSettings.h"

//Static functions


void Game::initVariables()
{
	window = NULL;
	dt = 0;
	gridSize = 64;
	mapSize = 100;
}



//Initializer functions

void Game::initGraphicsSettings()
{
	GraphicSettings.loadFromFile("Config/graphics.ini");
}

void Game::initWindow()
{

	if (GraphicSettings.fullscreen) {
		window = std::make_shared<sf::RenderWindow>(
			GraphicSettings.resolution,
			GraphicSettings.title,
			sf::Style::Fullscreen,
			GraphicSettings.contextSettings);
	}
	else {
		window = std::make_shared<sf::RenderWindow>(
			GraphicSettings.resolution,
			GraphicSettings.title,
			sf::Style::Titlebar | sf::Style::Close,
			GraphicSettings.contextSettings
			);
	}
	window->setFramerateLimit(GraphicSettings.frameRateLimit);
	window->setVerticalSyncEnabled(GraphicSettings.verticalSync);

}

void Game::initKeys()
{
	std::ifstream ifs("Config/supported_keys.ini");

	if (ifs.is_open()) {

		std::string key = "";
		int key_value = 0;

		while (ifs >> key >> key_value) {
			supportedKeys[key] = key_value;
		}

	}

	ifs.close();


	/*for (auto i : supportedKeys) {
		std::cout << i.first << " " << i.second << "\n";
	}*/

}

void Game::initStateData()
{
	stateData.window = window;
	stateData.GraphicsSettings = std::make_shared<GraphicsSettings>(GraphicSettings);
	stateData.states = &states;
	stateData.supportedKeys = std::make_shared< std::map < std::string, int >>(supportedKeys);
	stateData.gridSize = gridSize;
	stateData.mapSize = mapSize;
}

void Game::initStates()
{
	states.push(std::make_shared<MainMenuState>(std::make_shared<StateData>(stateData)));
}

//constructor functions
Game::Game()
{
	initVariables();
	initGraphicsSettings();
	initWindow();
	initKeys();
	initStateData();
	initStates();

}

Game::~Game()
{

	while (!states.empty())
	{
		states.pop();
	}

}

void Game::endApplication()
{
	//window.reset();
}

void Game::updateDt()
{
	/*Updates the dt variale with the time it takes to update and render one frame*/

	dt = dtClock.restart().asSeconds();
}

//Functions
void Game::updateSFMLEvents()
{
	while (window->pollEvent(sfEvent))
	{
		if (sfEvent.type == sf::Event::Closed)
			window->close();
	}

}

void Game::update()
{


	if (!states.empty()) {
		if (window->hasFocus()) {
			updateSFMLEvents();
			states.top()->update(dt);

			if (states.top()->getQuit()) {
				states.top()->endState();
				states.pop();
			}
		}
	}
	//Application end
	else {
		//endApplication();
		window->close();

	}
}

void Game::render()
{
	window->clear();

	//render items
	if (!states.empty())
		states.top()->render();
	window->display();
}

void Game::run()
{
	while (window->isOpen())
	{
		updateDt();
		update();
		render();
	}

}
