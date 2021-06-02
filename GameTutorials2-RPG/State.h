#pragma once

#include "Gui.h"

class Player;
class GraphicsSettings;
class State;

class StateData
{
public:
	StateData() {};
	float gridSize = 0.f;
	std::shared_ptr<GraphicsSettings> GraphicsSettings;
	std::shared_ptr<sf::RenderWindow> window;
	std::shared_ptr<std::map<std::string, int>> supportedKeys;
	std::stack<std::shared_ptr<State>>*  states;
	//variables
};

class State
{
public:

	//Constructor|Deconstructor
	State(std::shared_ptr<StateData>);
	virtual ~State();

	void endState();
	void pauseState();
	void unpauseState();

	//accessors
	const bool& getQuit() const;
	const bool getKeyTime();

	//Functions
	virtual void update(const float& dt) = 0;
	virtual void updateMousePositions();
	virtual void updateKeyTime(const float& dt);
	virtual void updateInput(const float& dt) = 0;
	virtual void render(std::shared_ptr<sf::RenderTarget> target =  NULL) = 0;

	


protected:
	
	//Variables
	std::shared_ptr<StateData> stateData;
	std::stack< std::shared_ptr<State>>* states; // this is a pointer to a stack of pointers from the game class
	std::shared_ptr<GraphicsSettings> gfxSettings;
	sf::Font font; //States font.
	
	bool quit;
	bool paused;
	float gridSize;
	float keyTime;
	float keyTimeMax;

	sf::Vector2i mousePosScreen; 
	sf::Vector2i mousePosWindow; 
	sf::Vector2f mousePosView;
	sf::Vector2u mousePosGrid;

	//Resources
	std::map <std::string, sf::Texture> textures;
	std::shared_ptr<sf::RenderWindow> window;
	std::shared_ptr<std::map<std::string, int>> supportedKeys;
	std::map<std::string, int> keybinds;

	//Functions
	virtual void initFont();
	virtual void initKeybinds() = 0;
	virtual std::unique_ptr<gui::Button> addButton(float x, float y, const std::string text, float width = 250.f, float height = 75.f, int characterSize = 50); //Basic Button
	virtual std::unique_ptr<gui::Button> addButton(float x, float y, const std::string text, float width, float height, int characterSize,
		sf::Color text_idle_color, sf::Color text_hover_color, sf::Color text_active_color,
		sf::Color idle_color, sf::Color hover_color, sf::Color active_color
	); //Fully Modifiable button

private:
	
};


