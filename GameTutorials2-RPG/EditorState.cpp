#include "stdafx.h"
#include "EditorState.h"
#include "GraphicsSettings.h"
#include "TileMap.h"
#include "Tile.h"
#include "PauseMenu.h"
#include "EditorModes.h"
#include "EnemyLibrary.h"
#include "TextTagSystem.h"

//Initializer functions
void EditorState::initVariables()
{
	cameraSpeed = 500.f;
	activeMode = 0;
	enemyLib = std::make_shared<EnemyLibrary>(std::shared_ptr<TextTagSystem>(), nullptr);
}

void EditorState::initEditorStateData()
{
	editorStateData = std::make_shared<EditorStateData>();
	editorStateData->keyTime = keyTime;
	editorStateData->keyTimeMax = keyTimeMax;
	editorStateData->characterSize = characterSize;
	editorStateData->font = font;
	editorStateData->view = view;
	editorStateData->keybinds = keybinds;
	editorStateData->mousePosGrid = mousePosGrid;
	editorStateData->mousePosScreen = mousePosScreen;
	editorStateData->mousePosView = mousePosView;
	editorStateData->mousePosWindow = mousePosWindow;
}

void EditorState::initView()
{
	view.setSize(sf::Vector2f((float)GraphicsSettings->resolution.width, (float)GraphicsSettings->resolution.height));
	view.setCenter(GraphicsSettings->resolution.width / 2.f, GraphicsSettings->resolution.height / 2.f);
}

void EditorState::initKeybinds()
{
	std::ifstream ifs("Config/editorstate_keybinds.ini");

	if (ifs.is_open()) {

		std::string key = "";
		std::string key2 = "";

		while (ifs >> key >> key2) {
			keybinds[key] = supportedKeys->at(key2);
		}

	}

	ifs.close();


}

void EditorState::initPauseMenu()
{
	sf::VideoMode& vm = GraphicsSettings->resolution;
	pmenu = std::make_shared<PauseMenu>(*window, font, gui::p2pX(13.f, vm), gui::p2pY(6.9f, vm),characterSize);
	pmenu->addButton("SAVE", gui::p2pY(34.f, vm), "Save"); //Key, Y, text
	pmenu->addButton("LOAD", gui::p2pY(48.f, vm), "Load"); //Key, Y, text
	pmenu->addButton("CLEAR",gui::p2pY(62.f, vm), "Clear"); //Key, Y, text
	pmenu->addButton("QUIT", gui::p2pY(76.f, vm), "Quit"); //Key, Y, text
}

void EditorState::initTexts()
{

}

void EditorState::initTileMap()
{
	map = std::make_shared<TileMap>("Save/mapfile", enemyLib);
	//map = std::make_unique<TileMap>(stateData->gridSize, mapSize, mapSize, "Resources/Images/Tiles/tilesheet3.png");
	//map->loadFromFile("Save/mapfile");
}

void EditorState::initModes()
{
	modes.push_back(std::make_unique<DefaultEditorMode>(stateData,map,editorStateData));
	modes.push_back(std::make_unique<EnemyEditorMode>(stateData, map, editorStateData));
}

void EditorState::initGui()
{
}

EditorState::EditorState(std::shared_ptr<StateData> state_data)
	: State(state_data)
{
	initVariables();
	initView();
	initTexts();
	initKeybinds();
	initPauseMenu();
	initTileMap();
	initGui();
	initEditorStateData();
	initModes();
	
}

EditorState::~EditorState()
{
}

void EditorState::updatePauseMenuButtons()
{
	if (pmenu->isButtonPressed("SAVE"))
		map->saveToFile("Save/mapfile");

	if (pmenu->isButtonPressed("LOAD"))
		map->loadFromFile("Save/mapfile");
	
	if (pmenu->isButtonPressed("CLEAR"))
		map->clear();
	
	if (pmenu->isButtonPressed("QUIT"))
		endState();
	
}

void EditorState::updateEditorInput(const float& dt)
{
	//Add a tile
	view;
}

void EditorState::updateInput(const float& dt)
{
	//open and close pause menu
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("CLOSE"))) && getKeyTime()) {
		if (!paused)
			pauseState();
		else
			unpauseState();
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("TOGGLE_MODE"))) && getKeyTime()) {
		if(activeMode < modes.size()-1)
		{
			activeMode++;
		}else
		{
			activeMode = 0;
		}
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(editorStateData->keybinds.at("MOVE_CAMERA_UP"))))
	{
		editorStateData->view.move(0.f, -cameraSpeed * dt);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(editorStateData->keybinds.at("MOVE_CAMERA_DOWN"))))
	{
		editorStateData->view.move(0.f, cameraSpeed * dt);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(editorStateData->keybinds.at("MOVE_CAMERA_LEFT"))))
	{
		editorStateData->view.move(-cameraSpeed * dt, 0.f);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(editorStateData->keybinds.at("MOVE_CAMERA_RIGHT"))))
	{
		editorStateData->view.move(cameraSpeed * dt, 0.f);
	}
	

}

void EditorState::updateButtons(const float& dt)
{
	/*Updates all the buttons and their states and handles their functionality*/
	for (auto& it : buttons)
	{
		it.second->update(dt, mousePosView);
	}
}

void EditorState::updateGui(const float& dt)
{
	
	
}

void EditorState::update(const float& dt)
{
	
	updateMousePositions(std::make_unique<sf::View>(editorStateData->view));
	updateKeyTime(dt);
	updateInput(dt);


	
	if (!paused) {
		modes.at(activeMode)->update(dt);
		updateButtons(dt);
	}
	else {
		pmenu->update(dt, sf::Vector2f((float)mousePosWindow.x, (float)mousePosWindow.y));
		updatePauseMenuButtons();
	}

	//player.update(dt);


}

void EditorState::renderButtons(std::shared_ptr<sf::RenderTarget> target)
{
	for (auto& it : buttons)
	{
		it.second->render(*target);
	}

}

void EditorState::renderGui(std::shared_ptr<sf::RenderTarget> target)
{
	if (!target)
		target = stateData->window;
	target->setView(editorStateData->view);
	//PauseMenu
	if (!paused) {
		target->setView(stateData->window->getDefaultView());
		
		modes.at(activeMode)->render(target);
	}
	else {
		target->setView(stateData->window->getDefaultView());
		pmenu->render(*target);
	}
	
}

void EditorState::render(std::shared_ptr<sf::RenderTarget> target)
{
	if (!target)
		target = stateData->window;
	target->setView(editorStateData->view);
	//PauseMenu
	if (!paused) {

		target->setView(stateData->window->getDefaultView());
		renderButtons(target);
		renderGui(target);
	}
	else {
		target->setView(stateData->window->getDefaultView());
		pmenu->render(*target);
	}
}





