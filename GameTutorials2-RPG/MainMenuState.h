#pragma once
#include "State.h"

class Gamestate;
class EditorState;
class SettingsState;

class MainMenuState :
    public State
{
private:
	//init functions
	void initVariables();
	void initGui();
	void initKeybinds();
public:
	MainMenuState(std::shared_ptr<StateData> state_data);
	virtual ~MainMenuState();

	//functions
	void updateInput(const float& dt);
	void updateButtons(const float& dt);
	void update(const float& dt);
	void render(std::shared_ptr<sf::RenderTarget> target);
	void renderButtons(sf::RenderTarget& target);
	void resetGui();
private:

	//variables 
	std::map<std::string, std::unique_ptr<gui::Button>> buttons; //main menu buttons
	sf::Texture bgTexture; //background texture
	sf::RectangleShape background;
	
	//functions

};

//tutorial 108 for box behind buttons if you want. 