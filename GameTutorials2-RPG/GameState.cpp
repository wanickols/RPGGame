#include "stdafx.h"
#include "GameState.h"
#include "TileMap.h"
#include "GraphicsSettings.h"
#include "PauseMenu.h"
#include "Player.h"
#include "PlayerGui.h"

void GameState::initDefferredRender()
{
	this->renderTexture.create(this->gfxSettings->resolution.width,
		this->gfxSettings->resolution.height,
		this->gfxSettings->contextSettings
	);

	this->renderSprite.setTexture(this->renderTexture.getTexture());
	this->renderSprite.setTextureRect(
		sf::IntRect(
			0,
			0,
			this->gfxSettings->resolution.width, 
			this->gfxSettings->resolution.height
		));
}

//initializer functions
void GameState::initView()
{
	this->view.setSize(sf::Vector2f((float)this->gfxSettings->resolution.width, (float)this->gfxSettings->resolution.height));
	//this->view.setCenter(this->gfxSettings->resolution.width / 2.f, this->gfxSettings->resolution.height / 2.f);

}

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
	this->pmenu = std::make_unique<PauseMenu>(*window, font, p2pX(13.f), p2pY(6.9f), this->characterSize);

	this->pmenu->addButton("SAVE", p2pY(34.f), "Save"); //Key, Y, 
	this->pmenu->addButton("STATS", p2pY(50.f), "Stats");
	this->pmenu->addButton("QUIT", p2pY(83.f), "Quit"); //Key, Y, text
}

void GameState::initTileMap()
{
	//CHANGE LATER TO GET LOADFROMFILE
	this->map = std::make_unique<TileMap>(this->stateData->gridSize, this->mapSize, this->mapSize, "Resources/Images/Tiles/tilesheet1.png");
	this->map->loadFromFile("Save/mapfile");
}

void GameState::initPlayers()
{
	this->player = std::make_unique<Player>(p2pX(11.4f), p2pY(20.3f), this->textures["PLAYER_SHEET"]);
}

void GameState::initPlayerGui()
{
	this->playerGui = std::make_shared<PlayerGui>(this->player, this->font);
	this->playerGuiMenuOpen = false;
	
}


//constructors
GameState::GameState(std::shared_ptr<StateData> state_data)
	: State(state_data)
{
	this->initDefferredRender();
	this->initView();
	this->initKeybinds();
	this->initTextures();
	this->initPauseMenu();
	this->initTileMap();
	this->initPlayers();
	this->initPlayerGui();
}


GameState::~GameState()
{
}

//Functions

void GameState::updateView()
{
	this->view.setCenter(std::floor(this->player->getPosition().x), std::floor(this->player->getPosition().y));
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
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::L) && this->getKeyTime())
		this->player->loseHealth(10);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::G) && this->getKeyTime())
		this->player->addExp(10);




}

void GameState::updatePlayerGui(const float& dt)
{
	this->playerGui->update(dt, sf::Vector2f((float)mousePosWindow.x, (float)mousePosWindow.y));
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

void GameState::updateTileMap(const float& dt)
{
	//std::shared_ptr<Entity> player1 = std::make_shared<Entity>(this->player);
	this->map->update();
	this->map->updateCollision(this->player, dt);
}

void GameState::update(const float& dt)
{

	this->updateMousePositions(std::make_unique<sf::View>(this->view));
	this->updateKeyTime(dt);
	this->updateInput(dt);
	if (!this->paused && !this->playerGuiMenuOpen) {

		this->updateView();
		this->updateTileMap(dt);
		this->updatePlayerInput(dt);
		this->updatePlayerGui(dt);

		this->player->update(dt);
		
	}
	else if (paused) {
		this->pmenu->update(sf::Vector2f((float)mousePosWindow.x, (float)mousePosWindow.y));
		this->updatePauseMenuButtons();
	}else	{
		
	}
}


void GameState::render(std::shared_ptr<sf::RenderTarget> target)
{
	if (!target)
		target = this->window;
	this->renderTexture.clear();

	//Player and Map
	this->renderTexture.setView(this->view);
	this->map->render(this->renderTexture, this->player->getGridPosition((int)this->stateData->gridSize));
	this->player->render(this->renderTexture);
	this->map->renderDeferred(this->renderTexture);
	
	//Player Gui
	this->renderTexture.setView(this->renderTexture.getDefaultView());
	this->playerGui->render(this->renderTexture);

	//Pause Menu
	if (this->paused) {
		
		this->pmenu->render(this->renderTexture);
	}
	
	//Final Render
	this->renderTexture.display();
	this->renderSprite.setTexture(this->renderTexture.getTexture());
	target->draw(this->renderSprite);
}





