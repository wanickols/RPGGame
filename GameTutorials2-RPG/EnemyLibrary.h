#pragma once

#include "Enemy.h"

class allEnemyPresets;
class TileMap;
class TextTagSystem;
class StateData;

class ComponentLibrary 
{
public:
	ComponentLibrary();
	std::shared_ptr<allEnemyPresets> add(tinyxml2::XMLElement*);
	std::map<std::string, int> componentTypes;


	void addHitbox(tinyxml2::XMLElement*, std::shared_ptr<allEnemyPresets> presets);
	void addMovement(tinyxml2::XMLElement*, std::shared_ptr<allEnemyPresets> presets);
	void addAttribute(tinyxml2::XMLElement*, std::shared_ptr<allEnemyPresets> presets);
	void addAnimation(tinyxml2::XMLElement*, std::shared_ptr<allEnemyPresets> presets);
	void addCombat(tinyxml2::XMLElement*, std::shared_ptr<allEnemyPresets> presets);
	void addEnemyData(tinyxml2::XMLElement*, std::shared_ptr<allEnemyPresets> presets);
	void addAI(tinyxml2::XMLElement*, std::shared_ptr<allEnemyPresets> presets);
};

class EnemyLibrary
{
public:
	void initComponents();
	EnemyLibrary(std::shared_ptr<TextTagSystem> textts, std::shared_ptr<Entity> player);
	std::shared_ptr<sf::Texture> find(std::string name);

	void initStateData(StateData& state_data);

	void update(const float& dt, bool playerAttack, std::shared_ptr<Entity> attacker, std::shared_ptr<TileMap> map);
	void render(sf::RenderTarget& target, sf::Shader* shader = NULL, sf::Vector2f light_position = sf::Vector2f(), const bool show_hitbox = false);
	std::string translateType(int type);
	bool createComponents(Enemy& enemy, std::string name, std::shared_ptr<EnemySpawner> spawner);

	std::vector<std::shared_ptr<Enemy>>& getEnemies();
	bool decreaseSpawn;
private:
	std::vector<std::shared_ptr<Enemy>> enemies;
	std::map<int, std::string> types; //assigning names to numbers
	std::map<std::string, std::shared_ptr<sf::Texture>> textures;
	std::map<std::string, std::shared_ptr<allEnemyPresets>> componentPresets;
	tinyxml2::XMLDocument textureDoc;
	tinyxml2::XMLDocument componentDoc;
	std::shared_ptr<StateData> stateData;
	ComponentLibrary componentLibrary;
	std::shared_ptr<Entity> player;
	std::shared_ptr<TextTagSystem> tts;
};

