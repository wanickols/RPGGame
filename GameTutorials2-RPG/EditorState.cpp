#include "stdafx.h"
#include "EditorState.h"
#include "Gui.h"
#include "TileMap.h"
#include "PauseMenu.h"

//Initializer functions
void EditorState::initVariables()
{
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
	this->pmenu->addButton("QUIT", 900.f, "Quit"); //Key, Y, text
}

void EditorState::initButtons()
{
}

void EditorState::initGui()
{
	this->selectorRect.setSize(sf::Vector2f(this->stateData->gridSize, this->stateData->gridSize));
	this->selectorRect.setFillColor(sf::Color::Transparent);
	this->selectorRect.setOutlineThickness(1.f);
	this->selectorRect.setOutlineColor(sf::Color::White);
}

void EditorState::initTileMap()
{
	this->map = std::make_unique<TileMap>(this->stateData->gridSize, 10, 10);
}

EditorState::EditorState(std::shared_ptr<StateData> state_data)
	: State(state_data)
{
	this->initVariables();
	this->initBackround();
	this->initFonts();
	this->initKeybinds();
	this->initPauseMenu();
	this->initButtons();
	this->initGui();
	this->initTileMap();

}

EditorState::~EditorState()
{
}

void EditorState::updatePauseMenuButtons()
{
	if (this->pmenu->isButtonPressed("QUIT"))
		this->endState();
}

void EditorState::updateInput(const float& dt)
{
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

void EditorState::updateGui()
{
	this->selectorRect.setPosition(mousePosGrid.x * gridSize, mousePosGrid.y * gridSize);
}

void EditorState::update(const float& dt)
{
	this->updateMousePositions();
	this->updateKeyTime(dt);
	this->updateInput(dt);
	if (!this->paused) {
		this->updateGui();
	}
	else {
		this->pmenu->update(sf::Vector2f((float)mousePosWindow.x, (float)mousePosWindow.y));
		this->updatePauseMenuButtons();
	}

	//this->player.update(dt);


}

void EditorState::render(std::shared_ptr<sf::RenderTarget> target)
{
	if (!target)
		target = this->window;

	

	//PauseMenu
	if (!this->paused) {

		this->renderButtons(*target);
		this->renderGui(*target);
	}
	else {
		this->pmenu->render(*target);
	}
}

void EditorState::renderGui(sf::RenderTarget& target)
{
	target.draw(this->selectorRect);
}

void EditorState::renderButtons(sf::RenderTarget& target)
{
	for (auto& it : this->buttons)
	{
		it.second->render(target);
	}
	this->map->render(target);
}

void EditorState::addTile()
{
}

void EditorState::removeTile()
{
}
