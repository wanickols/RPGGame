#pragma once

#include "State.h"

class Player;
class PlayerGui;
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
	void initShaders();
	void initTileMap();
	void initPlayers();
	void initPlayerGui();


public:
	GameState(std::shared_ptr<StateData> state_data);
	virtual ~GameState();

	//functions
	void updateView();
	void updatePlayerInput(const float& dt);
	void updatePlayerGui(const float& dt);
	void updateInput(const float& dt);
	void updatePauseMenuButtons();
	void updateTileMap(const float& dt);

	void update(const float& dt);
	void render(std::shared_ptr<sf::RenderTarget> target);

private:
	sf::View view;
	sf::RenderTexture renderTexture;
	sf::Vector2i viewGridPosition;
	sf::Sprite renderSprite;
	sf::Shader main_shader;


	std::unique_ptr<TileMap> map;
	std::shared_ptr<Player> player;
	std::shared_ptr<PlayerGui> playerGui;
	std::unique_ptr<PauseMenu> pmenu;

	bool playerGuiMenuOpen;
	//functions
};

