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
	void initBackround();
	void initKeybinds();
	void initButtons();

public:
	MainMenuState(std::shared_ptr<StateData> state_data);
	virtual ~MainMenuState();

	//functions
	void updateInput(const float& dt);
	void updateButtons();
	void update(const float& dt);
	void render(std::shared_ptr<sf::RenderTarget> target);
	void renderButtons(sf::RenderTarget& target);
private:

	//variables 
	std::map<std::string, std::unique_ptr<gui::Button>> buttons;
	sf::Texture bgTexture; //background texture;
	sf::RectangleShape background;
	
	//functions

};

