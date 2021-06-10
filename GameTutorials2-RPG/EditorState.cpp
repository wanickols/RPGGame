#include "stdafx.h"
#include "EditorState.h"
#include "GraphicsSettings.h"
#include "TileMap.h"
#include "Tile.h"
#include "PauseMenu.h"

//Initializer functions
void EditorState::initVariables()
{
	textureRect = sf::IntRect(0, 0, static_cast<int>(this->stateData->gridSize), static_cast<int>(this->stateData->gridSize));
	this->collision = false;
	this->Type = TileType::DEFAULT;
	this->cameraSpeed = 100.f;
}

void EditorState::initView()
{
	this->view.setSize(sf::Vector2f((float)this->gfxSettings->resolution.width, (float)this->gfxSettings->resolution.height));
	this->view.setCenter(this->gfxSettings->resolution.width / 2.f, this->gfxSettings->resolution.height / 2.f);
}

void EditorState::initBackround()
{

}

void EditorState::initFonts()
{
	if (!this->font.loadFromFile("Fonts/Dosis-Light.ttf")) {

		throw("ERROR::EDITORSTATE::COULD NOT LOAD FONT");
	}
}

void EditorState::initKeybinds()
{
	std::ifstream ifs("Config/editorstate_keybinds.ini");

	if (ifs.is_open()) {

		std::string key = "";
		std::string key2 = "";

		while (ifs >> key >> key2) {
			this->keybinds[key] = this->supportedKeys->at(key2);
		}

	}

	ifs.close();


}

void EditorState::initPauseMenu()
{
	this->pmenu = std::make_unique<PauseMenu>(*window, font);

	this->pmenu->addButton("SAVE", 400.f, "Save"); //Key, Y, text
	this->pmenu->addButton("LOAD", 500.f, "Load"); //Key, Y, text
	this->pmenu->addButton("CLEAR", 600.f, "Clear"); //Key, Y, text
	this->pmenu->addButton("QUIT", 700.f, "Quit"); //Key, Y, text
}

void EditorState::initTexts()
{
	this->cursorText.setFont(this->font);
	this->cursorText.setFillColor(sf::Color::White);
	this->cursorText.setCharacterSize(12);
}

void EditorState::initButtons()
{
}

void EditorState::initTileMap()
{
	this->map = std::make_unique<TileMap>(this->stateData->gridSize, 10, 10, "Resources/Images/Tiles/tilesheet1.png");
	this->map->loadFromFile("Save/mapfile");
}

void EditorState::initGui()
{
	this->sideBar.setSize(sf::Vector2f(80.f, (float)this->window->getSize().y));
	this->sideBar.setFillColor(sf::Color(50, 50, 50, 100));
	this->sideBar.setOutlineColor(sf::Color(200, 200, 200, 200));
	this->sideBar.setOutlineThickness(1.5f);

	this->selectorRect.setSize(sf::Vector2f(this->stateData->gridSize, this->stateData->gridSize));
	this->selectorRect.setFillColor(sf::Color(255, 255, 255, 180));
	this->selectorRect.setOutlineThickness(1.f);
	this->selectorRect.setOutlineColor(sf::Color::White);
	this->selectorRect.setTexture(this->map->getTileSheet());
	this->selectorRect.setTextureRect(this->textureRect);

	this->textureSelector = std::make_unique<gui::TextureSelector>(20.f, 20.f, 500.f, 500.f, this->stateData->gridSize, *this->map->getTileSheet(), this->font);
}

EditorState::EditorState(std::shared_ptr<StateData> state_data)
	: State(state_data)
{
	this->initVariables();
	this->initView();
	this->initBackround();
	this->initFonts();
	this->initTexts();
	this->initKeybinds();
	this->initPauseMenu();
	this->initButtons();
	this->initTileMap();
	this->initGui();
}

EditorState::~EditorState()
{
}

void EditorState::updatePauseMenuButtons()
{
	if (this->pmenu->isButtonPressed("SAVE"))
		this->map->saveToFile("Save/mapfile");

	if (this->pmenu->isButtonPressed("LOAD"))
		this->map->loadFromFile("Save/mapfile");
	
	if (this->pmenu->isButtonPressed("CLEAR"))
		this->map->clear();
	
	if (this->pmenu->isButtonPressed("QUIT"))
		this->endState();
	
}

void EditorState::updateEditorInput(const float& dt)
{
	//Add a tile
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->getKeyTime())
	{
		if (!this->textureSelector->getActive()) {
			map->addTile(this->mousePosGrid.x, this->mousePosGrid.y, 0, this->textureRect, this->collision, this->Type);
		}
		else {
			this->textureRect = this->textureSelector->getTextureRect();
		}
	}
	if (!this->textureSelector->getActive()) {
		//Remove a tile
		if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && this->getKeyTime())
		{

			map->removeTile(this->mousePosGrid.x, this->mousePosGrid.y, 0);
		}
		//Toggle Collisions with C button
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("TOGGLE_COLLISION"))) && this->getKeyTime())
		{
			if (this->collision)
				this->collision = false;
			else
				this->collision = true;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("INC_TYPE"))) && this->getKeyTime()) 
		{
			//needs limit of maxed type
			this->Type++;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("DEC_TYPE"))) && this->getKeyTime()) 
		{
			if (this->Type > 0)
				this->Type--;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_CAMERA_UP"))))
		{
			this->view.move(0.f, -cameraSpeed * dt);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_CAMERA_DOWN"))))
		{
			this->view.move(0.f, cameraSpeed * dt);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_CAMERA_LEFT"))))
		{
			this->view.move(-cameraSpeed * dt, 0.f);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_CAMERA_RIGHT"))))
		{
			this->view.move(cameraSpeed * dt, 0.f);
		}
	}

	/*if (this->textureSelector->getActive()) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right) && this->getKeyTime())
		{
			this->textureSelector->move(true); //right
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left) && this->getKeyTime())
		{
			this->textureSelector->move(false); //left
		}
	}*/
}

void EditorState::updateInput(const float& dt)
{
	//open and close pause menu
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("CLOSE"))) && this->getKeyTime()) {
		if (!this->paused)
			this->pauseState();
		else
			this->unpauseState();
	}
	

}

void EditorState::updateButtons()
{
	/*Updates all the buttons and their states and handles their functionality*/
	for (auto& it : this->buttons)
	{
		it.second->update(this->mousePosView);
	}
}

void EditorState::updateGui(const float& dt)
{
	this->textureSelector->update(sf::Vector2f(this->mousePosWindow), dt);

	if (!this->textureSelector->getActive()) {
		this->selectorRect.setTextureRect(this->textureRect);
		this->selectorRect.setPosition(mousePosGrid.x * gridSize, mousePosGrid.y * gridSize);
	}
	std::stringstream ss;
	ss << mousePosView.x << " " << this->mousePosView.y << "\n" 
	   << mousePosGrid.x << " " << this->mousePosGrid.y << "\n"
	   << "Collision: " << this->collision << "\n"
	   << "Type: " << this->Type;
	cursorText.setString(ss.str());
	this->cursorText.setPosition(this->mousePosWindow.x + 100.f, this->mousePosWindow.y - 50.f);

	
}

void EditorState::update(const float& dt)
{
	this->updateMousePositions(std::make_unique<sf::View>(this->view));
	this->updateKeyTime(dt);
	this->updateInput(dt);
	
	if (!this->paused) {
		this->updateGui(dt);
		this->updateEditorInput(dt);
		
			this->updateButtons();
			
	}
	else {
		this->pmenu->update(sf::Vector2f((float)mousePosWindow.x, (float)mousePosWindow.y));
		this->updatePauseMenuButtons();
	}

	//this->player.update(dt);


}

void EditorState::renderButtons(sf::RenderTarget& target)
{
	for (auto& it : this->buttons)
	{
		it.second->render(target);
	}

}

void EditorState::renderGui(sf::RenderTarget& target)
{
	
	this->textureSelector->render(target);
	
	target.setView(this->view);
	if (!this->textureSelector->getActive())
		target.draw(this->selectorRect);

	target.setView(this->window->getDefaultView());
	target.draw(this->cursorText);
	target.draw(sideBar);
}

void EditorState::render(std::shared_ptr<sf::RenderTarget> target)
{
	if (!target)
		target = this->window;
	target->setView(this->view);
	//PauseMenu
	if (!this->paused) {
		
		this->map->render(*target);

		target->setView(this->window->getDefaultView());
		this->renderButtons(*target);
		this->renderGui(*target);
	}
	else {
		target->setView(this->window->getDefaultView());
		this->pmenu->render(*target);
	}
}





