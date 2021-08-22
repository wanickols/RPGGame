#pragma once

class Player;

class progressBar 
{

public:
	progressBar(float frontWidth, float backWidth, float height, float xPos, float yPos, sf::Color backgroundColor,sf::Color fillColor, std::shared_ptr<Player>& player, sf::Font& font, int fontSize = 12);

	sf::RectangleShape ProgBarBack; //background
	sf::RectangleShape ProgBarIn; //content

	void update(const float& dt,float percentWidth, std::string textString = "N");
	void render(sf::RenderTarget& target);

private:
	std::string textString;
	sf::Text text;
	std::shared_ptr<Player> player;
	float height;
	float fullWidth;
	float percentWidth;
};


class PlayerGui
{
private:
	std::shared_ptr<Player> player;

	float tempPercent;

	//HPBar
	std::unique_ptr<progressBar> HPBar; //Health Bar Object
	std::string HPBarText; //words that go into hp

	//ExpBar
	std::unique_ptr<progressBar> ExpBar; //Exp Bar Object
	std::string ExpBarText; //words that go into exp

	//Functions
	void initBars(sf::Font& font);

public:
	PlayerGui(std::shared_ptr<Player> player, sf::Font& font);

	//Functions
	void updateBars(const float& dt);
	void update(const float& dt);
	void render(sf::RenderTarget& target);
};

