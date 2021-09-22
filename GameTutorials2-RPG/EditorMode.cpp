#include "stdafx.h"
#include "EditorMode.h"
#include "PauseMenu.h"
#include "State.h"

EditorMode::EditorMode(std::shared_ptr<StateData> state_data, std::shared_ptr<TileMap> tile_map, std::shared_ptr<EditorStateData> editor_state_data)
	:stateData(state_data), map(tile_map)
{
	editorStateData = editor_state_data;
	paused = false;
}

void EditorMode::updateKeyTime(const float& dt)
{
	if (editorStateData->keyTime < editorStateData->keyTimeMax) {
		editorStateData->keyTime += 100.f * dt;
	}
}

void EditorMode::updateMousePositions(sf::View& view)
{
	editorStateData->mousePosScreen = sf::Mouse::getPosition();
	editorStateData->mousePosWindow = sf::Mouse::getPosition(*stateData->window);


	stateData->window->setView(view);

	editorStateData->mousePosView = stateData->window->mapPixelToCoords(sf::Mouse::getPosition(*stateData->window));
	editorStateData->mousePosGrid =
		sf::Vector2i(
			static_cast<int>(editorStateData->mousePosView.x) / static_cast<int>(stateData->gridSize),
			static_cast<int>(editorStateData->mousePosView.y) / static_cast<int>(stateData->gridSize)
		);

	stateData->window->setView(stateData->window->getDefaultView());
}

const bool EditorMode::getKeyTime()
{
	if (editorStateData->keyTime > editorStateData->keyTimeMax)
	{
		editorStateData->keyTime = 0.f;
		return true;
	}
	return false;
}
