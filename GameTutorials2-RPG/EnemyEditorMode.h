#pragma once
#include "EditorMode.h"

class EnemyEditorMode : public EditorMode
{
public:
	EnemyEditorMode(std::shared_ptr<StateData> state_data, std::shared_ptr<TileMap> tile_map, std::shared_ptr<EditorStateData> editor_state_data);

	void updateInput(const float& dt);
	void updateGui(const float& dt);
	void update(const float& dt);

	void render(std::shared_ptr<sf::RenderTarget> target) override;
	void renderGui(std::shared_ptr<sf::RenderTarget> target) override;
private:
	void initGui();
	void initVariables();

	sf::Text cursorText;
	sf::RectangleShape sidebar;
	std::unique_ptr<gui::TextureSelector> textureSelector;
	std::map<std::string, std::unique_ptr<gui::Button>> buttons;
	sf::IntRect textureRect;
	sf::RectangleShape selectorRect;
	
	int type;
	int amount;
	int timeToSpawn;
	float maxDistance;
};

