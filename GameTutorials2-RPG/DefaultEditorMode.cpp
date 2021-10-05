#include "stdafx.h"
#include "DefaultEditorMode.h"
#include "TileMap.h"
#include "Tile.h"
#include "State.h"
#include "EditorState.h"
#include "PauseMenu.h"

void DefaultEditorMode::initVariables()
{
	textureRect = sf::IntRect(0, 0, static_cast<int>(stateData->gridSize), static_cast<int>(stateData->gridSize));
	collision = false;
	layer = 0;
	Type = TileType::DEFAULT;
	tileLock = false;
	cameraSpeed = 400.f;
	showCollision = true;
	
}

void DefaultEditorMode::initGui()
{
	//CursorText
	cursorText.setFont(editorStateData->font);
	cursorText.setFillColor(sf::Color::White);
	cursorText.setCharacterSize(editorStateData->characterSize / 4);

	//SideBar
	
	sideBar.setSize(sf::Vector2f(80.f, (float)stateData->window->getSize().y));
	sideBar.setFillColor(sf::Color(50, 50, 50, 100));
	sideBar.setOutlineColor(sf::Color(200, 200, 200, 200));
	sideBar.setOutlineThickness(1.5f);

	//Selector
	selectorRect.setSize(sf::Vector2f(stateData->gridSize, stateData->gridSize));
	selectorRect.setFillColor(sf::Color(255, 255, 255, 180));
	selectorRect.setOutlineThickness(1.f);
	selectorRect.setOutlineColor(sf::Color::White);
	selectorRect.setTexture(map->getTileSheet());
	selectorRect.setTextureRect(textureRect);

	textureSelector = std::make_unique<gui::TextureSelector>(20.f, 20.f, 1000.f, 500.f, stateData->gridSize, *map->getTileSheet(), editorStateData->font);
}


DefaultEditorMode::DefaultEditorMode(std::shared_ptr<StateData> state_data, std::shared_ptr<TileMap> tile_map, std::shared_ptr<EditorStateData> editor_state_data)
	: EditorMode(state_data, tile_map, editor_state_data)
{
	initVariables();
	initGui();
}

void DefaultEditorMode::updateInput(const float& dt)
{

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && getKeyTime())
	{
		if (!textureSelector->getActive()) {
			if (tileLock) {
				if (map->tileEmpty(editorStateData->mousePosGrid.x, editorStateData->mousePosGrid.y, layer))
					map->addTile(editorStateData->mousePosGrid.x, editorStateData->mousePosGrid.y, 0, textureRect, collision, Type);
			}
			else
				map->addTile(editorStateData->mousePosGrid.x, editorStateData->mousePosGrid.y, 0, textureRect, collision, Type);
		}
		else {
			textureRect = textureSelector->getTextureRect();
		}
	}
	if (!textureSelector->getActive()) {
		//Remove a tile
		if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && getKeyTime())
		{

			map->removeTile(editorStateData->mousePosGrid.x, editorStateData->mousePosGrid.y, 0);
		}
		//Toggle Collisions with C button
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(editorStateData->keybinds.at("TOGGLE_COLLISION"))) && getKeyTime()) //C key
		{
			if (collision)
				collision = false;
			else
				collision = true;
		}
		//Toggle Collisions with C button
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(editorStateData->keybinds.at("TOGGLE_LOCKED"))) && getKeyTime()) //C key
		{
			if (tileLock)
				tileLock = false;
			else
				tileLock = true;
		}
		//Shows Collision Hitbox with X
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(editorStateData->keybinds.at("SHOW_COLLISION"))) && getKeyTime())
		{
			if (showCollision)
				showCollision = false;
			else
				showCollision = true;
		}
		//Increases tile type with button E
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(editorStateData->keybinds.at("INC_TYPE"))) && getKeyTime())
		{
			//needs limit of maxed type
			Type++;
		}
		//Decereases tile type with button Q
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(editorStateData->keybinds.at("DEC_TYPE"))) && getKeyTime())
		{
			if (Type > 0)
				Type--;
		}
		
	}
}

void DefaultEditorMode::updateGui(const float& dt)
{
	textureSelector->update(sf::Vector2f(editorStateData->mousePosWindow), dt);

	if (!textureSelector->getActive()) {
		selectorRect.setTextureRect(textureRect);
		selectorRect.setPosition(editorStateData->mousePosGrid.x * stateData->gridSize, editorStateData->mousePosGrid.y * stateData->gridSize);
	}
	std::stringstream ss;
	ss << editorStateData->mousePosView.x << " " << editorStateData->mousePosView.y << "\n"
		<< editorStateData->mousePosGrid.x << " " << editorStateData->mousePosGrid.y << "\n"
		<< "Collision: " << collision << "\n"
		<< "Tiles: " << map->getLayerSize(editorStateData->mousePosGrid.x, editorStateData->mousePosGrid.y, layer) << "\n"
		<< "Type: " << Type << "\n"
		<< "Locked " << tileLock;
	cursorText.setString(ss.str());
	cursorText.setPosition(editorStateData->mousePosWindow.x + 100.f, editorStateData->mousePosWindow.y - 50.f);

	for (auto& it : buttons)
	{
		it.second->update(editorStateData->mousePosView);
	}
}

void DefaultEditorMode::update(const float& dt)
{
	updateMousePositions(editorStateData->view);
	updateKeyTime(dt);
	updateInput(dt);

	if (!paused) {
		updateGui(dt);
		updateInput(dt);

		//updateButtons();

	}else
	{
	
	}

}

void DefaultEditorMode::render(std::shared_ptr<sf::RenderTarget> target)
{
	renderGui(target);
	textureSelector->render(*target);
	
	target->setView(editorStateData->view);
	if (!textureSelector->getActive())
		target->draw(selectorRect);

	target->setView(stateData->window->getDefaultView());
	target->draw(cursorText);
	target->draw(sideBar);
	
}

void DefaultEditorMode::renderGui(std::shared_ptr<sf::RenderTarget>target)
{
	if (!target)
		target = stateData->window;
	target->setView(editorStateData->view);
	//PauseMenu
	if (!paused) {
		map->render(*target, editorStateData->mousePosGrid, sf::Vector2f(), NULL, true);
		map->renderDeferred(*target);
		target->setView(stateData->window->getDefaultView());
	//	renderButtons(*target);
	}
	else {
		target->setView(stateData->window->getDefaultView());
		//pmenu->render(*target);
	}
}
