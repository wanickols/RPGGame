#include "stdafx.h"
#include "Game.h"
#include "MainMenuState.h"
#include "GraphicsSettings.h"

//Static functions


void Game::initVariables()
{
	this->window = NULL;
	this->dt = 0;
	gridSize = 64;
	mapSize = 100;
}



//Initializer functions

void Game::initGraphicsSettings()
{
	this->GraphicSettings.loadFromFile("Config/graphics.ini");
}

void Game::initWindow()
{

	if (this->GraphicSettings.fullscreen) {
		this->window = std::make_shared<sf::RenderWindow>(
			this->GraphicSettings.resolution,
			this->GraphicSettings.title,
			sf::Style::Fullscreen,
			this->GraphicSettings.contextSettings);
	}
	else {
		this->window = std::make_shared<sf::RenderWindow>(
			this->GraphicSettings.resolution,
			this->GraphicSettings.title,
			sf::Style::Titlebar | sf::Style::Close,
			this->GraphicSettings.contextSettings
			);
	}
	this->window->setFramerateLimit(this->GraphicSettings.frameRateLimit);
	this->window->setVerticalSyncEnabled(this->GraphicSettings.verticalSync);

}

void Game::initKeys()
{
	std::ifstream ifs("Config/supported_keys.ini");

	if (ifs.is_open()) {

		std::string key = "";
		int key_value = 0;

		while (ifs >> key >> key_value) {
			this->supportedKeys[key] = key_value;
		}

	}

	ifs.close();


	for (auto i : supportedKeys) {
		std::cout << i.first << " " << i.second << "\n";
	}

}

void Game::initStateData()
{
	this->stateData.window = this->window;
	this->stateData.GraphicsSettings = std::make_shared<GraphicsSettings>(GraphicSettings);
	this->stateData.states = &this->states;
	this->stateData.supportedKeys = std::make_shared< std::map < std::string, int >>(this->supportedKeys);
	this->stateData.gridSize = gridSize;
	this->stateData.mapSize = mapSize;
}

void Game::initStates()
{
	this->states.push(std::make_shared<MainMenuState>(std::make_shared<StateData>(this->stateData)));
}

//constructor functions
Game::Game()
{
	this->initVariables();
	this->initGraphicsSettings();
	this->initWindow();
	this->initKeys();
	this->initStateData();
	this->initStates();

}

Game::~Game()
{

	while (!this->states.empty())
	{
		this->states.pop();
	}

}

void Game::endApplication()
{
	//this->window.reset();
}

void Game::updateDt()
{
	/*Updates the dt variale with the time it takes to update and render one frame*/

	this->dt = this->dtClock.restart().asSeconds();
}

//Functions
void Game::updateSFMLEvents()
{
	while (window->pollEvent(this->sfEvent))
	{
		if (sfEvent.type == sf::Event::Closed)
			window->close();
	}

}

void Game::update()
{


	if (!this->states.empty()) {
		if (this->window->hasFocus()) {
			this->updateSFMLEvents();
			this->states.top()->update(this->dt);

			if (this->states.top()->getQuit()) {
				this->states.top()->endState();
				this->states.pop();
			}
		}
	}
	//Application end
	else {
		this->endApplication();
		this->window->close();

	}
}

void Game::render()
{
	window->clear();

	//render items
	if (!this->states.empty())
		this->states.top()->render();
	window->display();
}

void Game::run()
{
	while (window->isOpen())
	{
		this->updateDt();
		this->update();
		this->render();
	}

}
