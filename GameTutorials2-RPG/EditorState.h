#pragma once
#include "TileMap.h"
#include "State.h"

class Gui;
class PauseMenu;
class TileMap;

class EditorState :
    public State	
{
private:
	//init functions
	void initVariables();
	void initBackround();
	void initPauseMenu();
	void initFonts();
	void initKeybinds();
	void initButtons();
	void initGui();
	void initTileMap();

public:
	EditorState(std::shared_ptr<StateData> state_data);
	virtual ~EditorState();

	//functions
	void updateInput(const float& dt);
	void updatePauseMenuButtons();
	void updateButtons();
	void updateGui();
	void update(const float& dt);
	void render(std::shared_ptr<sf::RenderTarget> target);
	void renderGui(sf::RenderTarget& target);
	void renderButtons(sf::RenderTarget& target);
private:

	//variables 
	sf::Font font;

	std::map<std::string, std::unique_ptr<gui::Button>> buttons;
	std::unique_ptr<TileMap> map;
	
	sf::RectangleShape selectorRect;

	sf::Texture bgTexture; //background texture;
	sf::RectangleShape background;
	std::unique_ptr<PauseMenu> pmenu;
	

	//functions
	void addTile();
	void removeTile();
};

