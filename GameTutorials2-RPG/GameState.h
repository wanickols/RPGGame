#pragma once

#include "State.h"

class Player;
class PauseMenu;
class TileMap;

class GameState : public State
{
private:
	//init functions
	void initDefferredRender();
	void initView();
	void initKeybinds();
	void initTextures();
	void initPauseMenu();
	void initTileMap();
	void initPlayers();


public:
	GameState(std::shared_ptr<StateData> state_data);
	virtual ~GameState();

	//functions
	void updateView();
	void updatePlayerInput(const float& dt);
	void updateInput(const float& dt);
	void updatePauseMenuButtons();
	void updateTileMap();

	void update(const float& dt);
	void render(std::shared_ptr<sf::RenderTarget> target);

private:
	sf::View view;
	sf::RenderTexture renderTexture;
	sf::Sprite renderSprite;

	std::unique_ptr<TileMap> map;
	std::shared_ptr<Player> player;
	std::unique_ptr<PauseMenu> pmenu;

	//functions
};

