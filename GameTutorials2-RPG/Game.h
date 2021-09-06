#pragma once
#include "MainMenuState.h"
#include "GraphicsSettings.h"

class MainMenuState;
class GraphicsSettings;
namespace sf
{
	class Event;
	class RenderWindow;
}

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
	float gridSize; //Size of one tile
	unsigned mapSize; //Size of map in tiles
	GraphicsSettings GraphicSettings;
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

