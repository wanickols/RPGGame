#pragma once
#include "EditorMode.h"

class gui::TextureSelector;
class PauseMenu;
struct EditorStateData;

class DefaultEditorMode : public EditorMode
{
private:
	//Init Functions
	void initVariables();
	void initGui(int& character_size);
public:
	DefaultEditorMode(std::shared_ptr<StateData> state_data, std::shared_ptr<TileMap> tile_map, std::shared_ptr<EditorStateData> editor_state_data);

	 void updateInput(const float& dt);
	 void updateGui(const float& dt);
	 void update(const float& dt);

	 void render(std::shared_ptr<sf::RenderTarget> target) override;
	 void renderGui(std::shared_ptr<sf::RenderTarget> target) override;

private:

	sf::View& view;
	sf::Font& font;
	sf::Text cursorText;
	sf::RectangleShape sideBar;
	std::unique_ptr<gui::TextureSelector> textureSelector;
	std::map<std::string, std::unique_ptr<gui::Button>> buttons;
	sf::IntRect textureRect;
	sf::RectangleShape selectorRect;
	int layer;
	bool collision;
	bool showCollision;
	short Type;
	bool tileLock;
	float cameraSpeed;
	
};

