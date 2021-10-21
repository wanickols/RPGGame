#include "stdafx.h"
#include "EnemyLibrary.h"
#include "Enemy.h"

EnemyLibrary::EnemyLibrary()
{
	//Init Textures
	textures["Rat"] = std::make_shared<sf::Texture>();
	if (!textures.at("Rat")->loadFromFile("Resources/Images/Sprites/Enemies/rat1.png"))
		std::cout << "ERROR::EnemyLibrary::FAILED TO LOAD RAT " << '\n';
	//textures["Bird"] = std::make_shared<sf::Texture>();
	//if (!textures.at("Bird")->loadFromFile("Resources/Images/Sprites/Enemies/bird1.png"))
		//std::cout << "ERROR::EnemyLibrary::FAILED TO LOAD BIRD " << '\n';

	int j = 0;
	auto iter = textures.begin();
	while (iter != textures.end()){
		types[0] = iter->first;
		j++; iter++;
	}
}

std::shared_ptr<sf::Texture> EnemyLibrary::find(std::string name)
{
	return textures.find(name)->second;
}

void EnemyLibrary::update(const float& dt)
{
	for (auto& i : enemies)
	{
		i->update(dt);
	}
}

void EnemyLibrary::render(sf::RenderTarget& target, sf::Shader* shader, sf::Vector2f light_position, const bool show_hitbox)
{
	for (auto& i : enemies)
	{
		i->render(target, shader, light_position, true);
	}
}

std::string EnemyLibrary::translateType(int type)
{
	return types.find(type)->second;
}

std::vector<std::shared_ptr<Enemy>>& EnemyLibrary::getEnemies()
{
	return enemies;
}
