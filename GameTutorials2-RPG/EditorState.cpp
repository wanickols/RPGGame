#include "stdafx.h"
#include "EditorState.h"
#include "GraphicsSettings.h"
#include "TileMap.h"
#include "Tile.h"
#include "PauseMenu.h"

//Initializer functions
void EditorState::initVariables()
{
	textureRect = sf::IntRect(0, 0, static_cast<int>(stateData->gridSize), static_cast<int>(stateData->gridSize));
	collision = false;
	layer = 0;
	Type = TileType::DEFAULT;
	tileLock = false;
	cameraSpeed = 400.f;
	showCollision = true;
}

void EditorState::initView()
{
	view.setSize(sf::Vector2f((float)GraphicsSettings->resolution.width, (float)GraphicsSettings->resolution.height));
	view.setCenter(GraphicsSettings->resolution.width / 2.f, GraphicsSettings->resolution.height / 2.f);
}

void EditorState::initBackround()
{

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
	pmenu = std::make_unique<PauseMenu>(*window, font, gui::p2pX(13.f, vm), gui::p2pY(6.9f, vm),characterSize);
	pmenu->addButton("SAVE", gui::p2pY(34.f, vm), "Save"); //Key, Y, text
	pmenu->addButton("LOAD", gui::p2pY(48.f, vm), "Load"); //Key, Y, text
	pmenu->addButton("CLEAR",gui::p2pY(62.f, vm), "Clear"); //Key, Y, text
	pmenu->addButton("QUIT", gui::p2pY(76.f, vm), "Quit"); //Key, Y, text
}

void EditorState::initTexts()
{
	cursorText.setFont(font);
	cursorText.setFillColor(sf::Color::White);
	cursorText.setCharacterSize(characterSize/4);
}

void EditorState::initButtons()
{
}

void EditorState::initTileMap()
{
	map = std::make_unique<TileMap>(stateData->gridSize, mapSize, mapSize, "Resources/Images/Tiles/tilesheet3.png");
	map->loadFromFile("Save/mapfile");
}

void EditorState::initGui()
{
	sideBar.setSize(sf::Vector2f(80.f, (float)window->getSize().y));
	sideBar.setFillColor(sf::Color(50, 50, 50, 100));
	sideBar.setOutlineColor(sf::Color(200, 200, 200, 200));
	sideBar.setOutlineThickness(1.5f);

	selectorRect.setSize(sf::Vector2f(stateData->gridSize, stateData->gridSize));
	selectorRect.setFillColor(sf::Color(255, 255, 255, 180));
	selectorRect.setOutlineThickness(1.f);
	selectorRect.setOutlineColor(sf::Color::White);
	selectorRect.setTexture(map->getTileSheet());
	selectorRect.setTextureRect(textureRect);

	textureSelector = std::make_unique<gui::TextureSelector>(20.f, 20.f, 1000.f, 500.f, stateData->gridSize, *map->getTileSheet(), font);
}

EditorState::EditorState(std::shared_ptr<StateData> state_data)
	: State(state_data)
{
	initVariables();
	initView();
	initBackround();
	initTexts();
	initKeybinds();
	initPauseMenu();
	initButtons();
	initTileMap();
	initGui();
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
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && getKeyTime())
	{
		if (!textureSelector->getActive()) {
			if (tileLock) {
				if (map->tileEmpty(mousePosGrid.x, mousePosGrid.y, layer))
					map->addTile(mousePosGrid.x, mousePosGrid.y, 0, textureRect, collision, Type);
			}else
				map->addTile(mousePosGrid.x, mousePosGrid.y, 0, textureRect, collision, Type);
		}
		else {
			textureRect = textureSelector->getTextureRect();
		}
	}
	if (!textureSelector->getActive()) {
		//Remove a tile
		if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && getKeyTime())
		{

			map->removeTile(mousePosGrid.x, mousePosGrid.y, 0);
		}
		//Toggle Collisions with C button
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("TOGGLE_COLLISION"))) && getKeyTime()) //C key
		{
			if (collision)
				collision = false;
			else
				collision = true;
		}
		//Toggle Collisions with C button
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("TOGGLE_LOCKED"))) && getKeyTime()) //C key
		{
			if (tileLock)
				tileLock = false;
			else
				tileLock = true;
		}
		//Shows Collision Hitbox with X
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("SHOW_COLLISION"))) && getKeyTime())
		{
			if (showCollision)
				showCollision = false;
			else
				showCollision = true;
		}
		//Increases tile type with button E
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("INC_TYPE"))) && getKeyTime()) 
		{
			//needs limit of maxed type
			Type++;
		}
		//Decereases tile type with button Q
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("DEC_TYPE"))) && getKeyTime()) 
		{
			if (Type > 0)
				Type--;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("MOVE_CAMERA_UP"))))
		{
			view.move(0.f, -cameraSpeed * dt);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("MOVE_CAMERA_DOWN"))))
		{
			view.move(0.f, cameraSpeed * dt);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("MOVE_CAMERA_LEFT"))))
		{
			view.move(-cameraSpeed * dt, 0.f);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("MOVE_CAMERA_RIGHT"))))
		{
			view.move(cameraSpeed * dt, 0.f);
		}
	}

	/*if (textureSelector->getActive()) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right) && getKeyTime())
		{
			textureSelector->move(true); //right
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left) && getKeyTime())
		{
			textureSelector->move(false); //left
		}
	}*/
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
	

}

void EditorState::updateButtons()
{
	/*Updates all the buttons and their states and handles their functionality*/
	for (auto& it : buttons)
	{
		it.second->update(mousePosView);
	}
}

void EditorState::updateGui(const float& dt)
{
	textureSelector->update(sf::Vector2f(mousePosWindow), dt);

	if (!textureSelector->getActive()) {
		selectorRect.setTextureRect(textureRect);
		selectorRect.setPosition(mousePosGrid.x * gridSize, mousePosGrid.y * gridSize);
	}
	std::stringstream ss;
	ss << mousePosView.x << " " << mousePosView.y << "\n"
		<< mousePosGrid.x << " " << mousePosGrid.y << "\n"
		<< "Collision: " << collision << "\n"
		<< "Tiles: " << map->getLayerSize(mousePosGrid.x, mousePosGrid.y, layer) << "\n"
		<< "Type: " << Type << "\n"
		<< "Locked " << tileLock;
	cursorText.setString(ss.str());
	cursorText.setPosition(mousePosWindow.x + 100.f, mousePosWindow.y - 50.f);

	
}

void EditorState::update(const float& dt)
{
	updateMousePositions(std::make_unique<sf::View>(view));
	updateKeyTime(dt);
	updateInput(dt);
	
	if (!paused) {
		updateGui(dt);
		updateEditorInput(dt);
		
			updateButtons();
			
	}
	else {
		pmenu->update(sf::Vector2f((float)mousePosWindow.x, (float)mousePosWindow.y));
		updatePauseMenuButtons();
	}

	//player.update(dt);


}

void EditorState::renderButtons(sf::RenderTarget& target)
{
	for (auto& it : buttons)
	{
		it.second->render(target);
	}

}

void EditorState::renderGui(sf::RenderTarget& target)
{
	
	textureSelector->render(target);
	
	target.setView(view);
	if (!textureSelector->getActive())
		target.draw(selectorRect);

	target.setView(window->getDefaultView());
	target.draw(cursorText);
	target.draw(sideBar);
}

void EditorState::render(std::shared_ptr<sf::RenderTarget> target)
{
	if (!target)
		target = window;
	target->setView(view);
	//PauseMenu
	if (!paused) {
		
		map->render(*target, mousePosGrid, sf::Vector2f(), NULL, showCollision);
		map->renderDeferred(*target);

		target->setView(window->getDefaultView());
		renderButtons(*target);
		renderGui(*target);
	}
	else {
		target->setView(window->getDefaultView());
		pmenu->render(*target);
	}
}





