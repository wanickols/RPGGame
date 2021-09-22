#pragma once
class StateData;
class TileMap;
class PauseMenu;

struct EditorStateData
{
	float keyTime;
	float keyTimeMax;
	int characterSize;
	sf::View view;
	sf::Font font;
	std::map < std::string, int> keybinds;
	sf::Vector2i mousePosScreen;
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;
	sf::Vector2i mousePosGrid;
};

class EditorMode
{
public:
	EditorMode(std::shared_ptr<StateData> state_data, std::shared_ptr<TileMap> tile_map, std::shared_ptr<EditorStateData> editor_state_data);

	virtual void updateInput(const float& dt) = 0;
	virtual void updateGui(const float& dt) = 0;
	virtual void updateKeyTime(const float& dt);
	virtual void updateMousePositions(sf::View& view);
	virtual void update(const float& dt) = 0;

	virtual void render(std::shared_ptr<sf::RenderTarget> target) = 0;
	virtual void renderGui(std::shared_ptr<sf::RenderTarget> target) = 0;
	const bool getKeyTime();

protected:

	std::shared_ptr<TileMap> map;
	std::shared_ptr<StateData> stateData;
	std::shared_ptr<EditorStateData> editorStateData;
	bool paused;
};

