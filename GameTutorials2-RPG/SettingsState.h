#pragma once
#include "State.h"

class SettingsState :
	public State
{
private:
	//Variables
	sf::Texture backgroundTexture;
	sf::RectangleShape background;

	std::map<std::string, std::unique_ptr<gui::Button>> buttons;
	std::map<std::string, std::unique_ptr<gui::DropDownList>> dropDownLists;

	sf::Text optionsText;

	std::vector<sf::VideoMode> modes;

	//Functions
	void initVariables();
	void initKeybinds();
	void initGui();
	void resetGui();
	void initText();

public:
	SettingsState(std::shared_ptr<StateData> state_data);
	virtual ~SettingsState();

	//Accessors

	//Functions
	void updateInput(const float& dt);
	void updateGui(const float& dt);
	void update(const float& dt);
	void renderGui(sf::RenderTarget& target);
	void render(std::shared_ptr<sf::RenderTarget> target);
};

