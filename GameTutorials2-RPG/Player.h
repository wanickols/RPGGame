#pragma once
#include "Entity.h"
class Bullet;
class FireRune;
class Rune;
class TileMap;

class Player :
	public Entity
{
private:
	//Init Functions
	void initVariables();
	void initComponents();
	void initAnimations(sf::Texture& texture_sheet, float x, float y);
	void initRunes();
public:
	//Constructors
	Player() = delete;
	Player(float x, float y, sf::Texture& texture);
	virtual ~Player();

	//Accessors
	const std::shared_ptr<Rune> getActiveRune();


	//Functions
	void updateBulletCollision(const float& dt, std::shared_ptr<TileMap> map);
	void updateAnimation(const float& dt, const sf::Vector2f mousePosView);
	virtual void update(const float& dt, const sf::Vector2f mousePosView);
	virtual void render(sf::RenderTarget& target, sf::Shader* shader = NULL, sf::Vector2f light_position = sf::Vector2f(),  const bool show_hitbox = false);
private:
	sf::Shader bullet_shader;
	std::vector< std::shared_ptr<Rune> > runes;
	std::shared_ptr <Rune> activeRune;
	//variables
	bool attacking;
};

