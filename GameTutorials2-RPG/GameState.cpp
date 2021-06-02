#include "stdafx.h"
#include "GameState.h"
#include "PauseMenu.h"
#include "Player.h"

//initializer functions
void GameState::initKeybinds()
{
	std::ifstream ifs("Config/gamestate_keybinds.ini");

	if (ifs.is_open()) {

		std::string key = "";
		std::string key2 = "";

		while (ifs >> key >> key2) {
			this->keybinds[key] = this->supportedKeys->at(key2);
		}

	}

	ifs.close();


}

void GameState::initTextures()
{
	if (!this->textures["PLAYER_SHEET"].loadFromFile("Resources/Images/Sprites/Player/PLAYER_SHEET.png")) {
		throw "ERROR::GAME_STATE::COULD_NOT_LOAD_PLAYER_SHEET_TEXTURE";
	}
}

void GameState::initPauseMenu()
{
	this->pmenu = std::make_unique<PauseMenu>(*window, font);

	this->pmenu->addButton("SAVE", 400.f, "Save"); //Key, Y, text
	this->pmenu->addButton("QUIT", 900.f, "Quit"); //Key, Y, text
}

void GameState::initTileMap()
{
	//CHANGE LATER TO GET LOADFROMFILE
	this->map = std::make_unique<TileMap>(this->stateData->gridSize, 10, 10);
}

void GameState::initPlayers()
{
	this->player = std::make_unique<Player>(220.f, 220.f, this->textures["PLAYER_SHEET"]);
}


//constructors
GameState::GameState(std::shared_ptr<StateData> state_data)
	: State(state_data)
{

	this->initKeybinds();
	this->initTextures();
	this->initPauseMenu();
	this->initTileMap();
	this->initPlayers();
}


GameState::~GameState()
{
}

void GameState::updatePlayerInput(const float& dt)
{
	//Player input
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("Move_Up"))))
		this->player->move(0.f, -1.f, dt);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("Move_Left"))))
		this->player->move(-1.f, 0.f, dt);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("Move_Down"))))
		this->player->move(0.f, 1.f, dt);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("Move_Right"))))
		this->player->move(1.f, 0.f, dt);



}

void GameState::updateInput(const float& dt)
{

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("CLOSE"))) && this->getKeyTime()) {
		if (!this->paused)
			this->pauseState();
		else
			this->unpauseState();
	}
}

void GameState::updatePauseMenuButtons()
{
	if (this->pmenu->isButtonPressed("QUIT"))
		this->endState();
}

void GameState::update(const float& dt)
{

	this->updateMousePositions();
	this->updateKeyTime(dt);
	this->updateInput(dt);
	if (!this->paused) {
		this->updatePlayerInput(dt);

		this->player->update(dt);
	}
	else {
		this->pmenu->update(sf::Vector2f((float)mousePosWindow.x, (float)mousePosWindow.y));
		this->updatePauseMenuButtons();
	}
}


void GameState::render(std::shared_ptr<sf::RenderTarget> target)
{
	if (!target)
		target = this->window;

	//this->map.render(*target);
	this->player->render(*target);

	if (this->paused) {
		this->pmenu->render(*target);
	}
}





