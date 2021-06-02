#pragma once
#include "GraphicsSettings.h"
#include "MainMenuState.h"

class MainMenuState;
class GraphicsSettings;

class Game
{
public:
	Game();
	virtual ~Game();

	//functions

	//regular
	void endApplication();

	//Updates
	void updateDt();
	void updateSFMLEvents();
	void update();
	void render();
	void run();

private:
	//Classes


	//variables
	StateData stateData;
	float gridSize;
	GraphicsSettings gfxSettings;
	std::shared_ptr<sf::RenderWindow> window;
	sf::Event sfEvent;

	std::stack<std::shared_ptr<State>> states; // the original states stack
	sf::Clock dtClock;
	float dt; /*DeltaTime*/

	std::map<std::string, int> supportedKeys;

	//Initializer functions
	void initVariables();
	void initGraphicsSettings();
	void initWindow();
	void initKeys();
	void initStateData();
	void initStates();


};

