#pragma once
#include "TileMap.h"
#include "State.h"

class PauseMenu;
class TileMap;
class EditorMode;
struct EditorStateData;

enum EditorModes { DefaultMode = 1, EnemyMode };



class EditorState :
    public State	
{
private:
	//init functions
	void initVariables();
	void initEditorStateData();
	void initView();
	void initPauseMenu();
	void initTexts();
	void initKeybinds();
	void initGui();
	void initTileMap();

	void initModes();


public:
	EditorState(std::shared_ptr<StateData> state_data);
	virtual ~EditorState();

	//functions
	void updateInput(const float& dt);
	void updatePauseMenuButtons();
	void updateEditorInput(const float& dt);
	void updateButtons();
	void updateGui(const float& dt);
	void update(const float& dt);
	void render(std::shared_ptr<sf::RenderTarget> target);
	void renderGui(std::shared_ptr<sf::RenderTarget> target);
	void renderButtons(std::shared_ptr<sf::RenderTarget> target);
private:

	//variables 
	std::shared_ptr<EditorStateData> editorStateData;
	
	sf::View view;

	std::map<std::string, std::unique_ptr<gui::Button>> buttons;
	std::shared_ptr<TileMap> map;

	
	
	std::vector<std::unique_ptr<EditorMode>> modes;
	int activeMode;
	float cameraSpeed;
	std::shared_ptr<EnemyLibrary> enemyLib;
	std::shared_ptr<PauseMenu> pmenu;
	
	

	//functions
};

