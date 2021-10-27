#include "stdafx.h"
#include "EnemyEditorMode.h"
#include "TileMap.h"
#include "State.h"
#include "GraphicsSettings.h"
#include "Tile.h"
#include "StateData.h"


void EnemyEditorMode::initGui()
{
	textureRect = sf::IntRect(192, 320, static_cast<int>(stateData->gridSize), static_cast<int>(stateData->gridSize));

	//CursorText
	cursorText.setFont(editorStateData->font);
	cursorText.setFillColor(sf::Color::White);
	cursorText.setCharacterSize(12);
	cursorText.setPosition(editorStateData->mousePosView.x, editorStateData->mousePosView.y);

	//General GUI
	sidebar.setSize(sf::Vector2f(80.f, static_cast<float>(stateData->GraphicsSettings->resolution.height)));
	sidebar.setFillColor(sf::Color(50, 50, 50, 100));
	sidebar.setOutlineColor(sf::Color(200, 200, 200, 150));
	sidebar.setOutlineThickness(1.f);

	selectorRect.setSize(sf::Vector2f(stateData->gridSize, stateData->gridSize));

	selectorRect.setSize(sf::Vector2f(stateData->gridSize, stateData->gridSize));
	selectorRect.setFillColor(sf::Color(255, 255, 255, 180));
	selectorRect.setOutlineThickness(1.f);
	selectorRect.setOutlineColor(sf::Color::White);
	selectorRect.setTexture(map->getTileSheet());
	selectorRect.setTextureRect(textureRect);

	//textureSelector = std::make_unique<gui::TextureSelector>(20.f, 20.f, 1000.f, 500.f, stateData->gridSize, *map->getTileSheet(), editorStateData->font);
}

void EnemyEditorMode::initVariables()
{
	
	type = 0;
	amount = 1;
	timeToSpawn = 60;
	maxDistance = 1000.f;
	enemyLevel = 1;
}

EnemyEditorMode::EnemyEditorMode(std::shared_ptr<StateData> state_data, std::shared_ptr<TileMap> tile_map, std::shared_ptr<EditorStateData> editor_state_data)
	: EditorMode(state_data, tile_map, editor_state_data)
{
	initVariables();
	initGui();
}

void EnemyEditorMode::updateInput(const float& dt)
{
	//Add a tile to the tilemap
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && getKeyTime())
	{
		if (!sidebar.getGlobalBounds().contains(sf::Vector2f(editorStateData->mousePosWindow)))
		{
			map->addEnemyTile(editorStateData->mousePosGrid.x, editorStateData->mousePosGrid.y, 0, textureRect,
				type, amount, timeToSpawn, maxDistance, enemyLevel);
		}
	}
	//Remove a tile from the tilemap
	else if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && getKeyTime())
	{
		if (!sidebar.getGlobalBounds().contains(sf::Vector2f(editorStateData->mousePosWindow)))
		{
			map->removeTile(editorStateData->mousePosGrid.x, editorStateData->mousePosGrid.y, 0, true);
		}
	}

	//Toggle collision
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(editorStateData->keybinds.at("INC_TYPE"))) && getKeyTime())
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
		{
			if (type > 0)
				type--;
			else
				type = 1;

		}
		else if (type < 1)
			type++;
		else
			type = 0;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(editorStateData->keybinds.at("AMOUNT_UP"))) && getKeyTime())
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
		{
			if (amount > 0) {
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
					amount -= 10;
				else
					--amount;
			}
			else
				amount = 99;
		}
		else if (amount < 100) {
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
				amount += 10;
			else
				++amount;
		}
		else
			amount = 0;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(editorStateData->keybinds.at("TTS_UP"))) && getKeyTime())
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
		{
			if (timeToSpawn > 0){
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
					timeToSpawn -= 10;
				else
				--timeToSpawn; 
			}
			else
				timeToSpawn = 600;
		}
		else if (timeToSpawn < 601) {
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
				timeToSpawn += 10;
			else
			++timeToSpawn;
		}
		else
			timeToSpawn = 0;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(editorStateData->keybinds.at("MD_UP"))) && getKeyTime())
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
		{
			if (maxDistance > 0) {
				
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
					maxDistance -= 10;
				else
					--maxDistance;
			}
			else
				maxDistance = 999;
		}
		else if (maxDistance < 1000) {
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
				maxDistance += 10;
			else
				++maxDistance;
		}
		else
			maxDistance = 0;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(editorStateData->keybinds.at("LEVEL_UP"))) && getKeyTime())
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
		{
			if (enemyLevel > 0) {
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
					enemyLevel -= 10;
				else
					--enemyLevel;
			}
			else
				enemyLevel = 0;
		}
		else {
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
				enemyLevel += 10;
			else
				++enemyLevel;
		}
	}
}

void EnemyEditorMode::updateGui(const float& dt)
{
	
	selectorRect.setTextureRect(textureRect);
	selectorRect.setPosition(editorStateData->mousePosGrid.x * stateData->gridSize, editorStateData->mousePosGrid.y * stateData->gridSize);
	
	std::stringstream ss;
	ss <<
		"\n" << "Enemy type: " << type <<
		"\n" << "Enemy amount: " << amount <<
		"\n" << "Time to spawn: " << timeToSpawn <<
		"\n" << "Level: " << enemyLevel <<
		"\n" << "Max distance: " << maxDistance;

	cursorText.setString(ss.str());
	cursorText.setPosition(editorStateData->mousePosWindow.x + 100.f, editorStateData->mousePosWindow.y - 50.f);
}

void EnemyEditorMode::update(const float& dt)
{
	updateMousePositions(editorStateData->view);
	updateKeyTime(dt);
	updateInput(dt);

	if (!paused) {
		updateInput(dt);
		updateGui(dt);
	}
}

void EnemyEditorMode::renderGui(std::shared_ptr<sf::RenderTarget> target)
{
	target->setView(editorStateData->view);

	if(!paused)
	{
		map->render(*target, editorStateData->mousePosGrid, sf::Vector2f(), NULL, true, true);
		map->renderDeferred(*target);
	

	
	target->draw(selectorRect);
	target->setView(stateData->window->getDefaultView());
	target->draw(cursorText);

	
	}
}

void EnemyEditorMode::render(std::shared_ptr<sf::RenderTarget> target)
{
	renderGui(target);
}


