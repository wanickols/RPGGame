#pragma once
#include "TileMap.h"
#include "State.h"

class State;
class PauseMenu;
class TileMap;

class GameState : public State
{
private:
	//init functions
	void initKeybinds();
	void initTextures();
	void initPauseMenu();
	void initTileMap();
	void initPlayers();


public:
	GameState(std::shared_ptr<StateData> state_data);
	virtual ~GameState();

	//functions
	void updatePlayerInput(const float& dt);
	void updateInput(const float& dt);
	void updatePauseMenuButtons();

	void update(const float& dt);
	void render(std::shared_ptr<sf::RenderTarget> target);

private:
	
	std::unique_ptr<TileMap> map;
	std::unique_ptr<Player> player;
	std::unique_ptr<PauseMenu> pmenu;

	//functions
};

