#pragma once

#include "Enemy.h"

class allEnemyPresets;

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
	void addAI(tinyxml2::XMLElement*, std::shared_ptr<allEnemyPresets> presets);
};

class EnemyLibrary
{
public:
	void initComponents();
	EnemyLibrary();
	std::shared_ptr<sf::Texture> find(std::string name);

	void update(const float& dt, bool playerAttack, std::shared_ptr<Entity> attacker);
	void render(sf::RenderTarget& target, sf::Shader* shader = NULL, sf::Vector2f light_position = sf::Vector2f(), const bool show_hitbox = false);
	std::string translateType(int type);
	bool createComponents(Enemy& enemy, std::string name, int x, int y);

	std::vector<std::shared_ptr<Enemy>>& getEnemies();
private:
	std::vector<std::shared_ptr<Enemy>> enemies;
	std::map<int, std::string> types; //assigning names to numbers
	std::map<std::string, std::shared_ptr<sf::Texture>> textures;
	std::map<std::string, std::shared_ptr<allEnemyPresets>> componentPresets;
	tinyxml2::XMLDocument textureDoc;
	tinyxml2::XMLDocument componentDoc;
	ComponentLibrary componentLibrary;

};

