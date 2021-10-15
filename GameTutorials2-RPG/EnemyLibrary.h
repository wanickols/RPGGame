#pragma once

#include "Enemy.h"


class EnemyLibrary
{
public:
	EnemyLibrary();
	std::shared_ptr<sf::Texture> find(std::string name);

	void update(const float& dt);
	void render(sf::RenderTarget& target, sf::Shader* shader = NULL, sf::Vector2f light_position = sf::Vector2f(), const bool show_hitbox = false);
	std::string translateType(int type);

	std::vector<std::shared_ptr<Enemy>>& getEnemies();
private:
	std::vector<std::shared_ptr<Enemy>> enemies;
	std::map<int, std::string> types;
	std::map<std::string, std::shared_ptr<sf::Texture>> textures;


};

