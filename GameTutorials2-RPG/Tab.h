#pragma once

class Entity;

class Tab
{
public:
	Tab(sf::VideoMode& vm, sf::Font& font, std::shared_ptr<Entity> player, bool hidden);
	virtual ~Tab();

	//Accessor
	const bool& getHidden() const;
	const bool& getOpen() const;
	void toggle();

	//Functions
	void hide();
	void show();

	virtual void update() = 0;
	virtual void render(sf::RenderTarget& target) = 0;
protected:
	sf::VideoMode& vm;
	sf::Font& font;
	std::shared_ptr<Entity> player;
	bool hidden;

};
