#pragma once

class Player;
class gui::Button;

class progressBar 
{

public:
	progressBar(float frontWidth, float backWidth, float height, float xPos, float yPos, sf::Color backgroundColor,sf::Color fillColor, std::shared_ptr<Player>& player, sf::Font& font, int offset = 0, int fontSize = 12);

	sf::RectangleShape ProgBarBack; //background
	sf::RectangleShape ProgBarIn; //content

	void update(const float& dt,float& percentWidth);
	void update(const float& dt, float& percentWidth, std::string textString);
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


	//variables
	float tempPercent;
	std::map < std::string, std::unique_ptr<gui::Button>> buttons; //buttons
	sf::Font& font;

	//HPBar
	std::unique_ptr<progressBar> HPBar; //Health Bar Object
	std::string HPBarText; //words that go into hp

	//ExpBar
	std::unique_ptr<progressBar> ExpBar; //Exp Bar Object
	std::string ExpBarText; //words that go into exp

	//Functions
	void initLevel();
	void initBars();


public:
	PlayerGui(std::shared_ptr<Player> player, sf::Font& font);

	//Functions
	void addButton(const std::string& key, const float& x, const float& y, const float& width, const float& height, const std::string& text, const short& textSize = 12);
	void addButton(const std::string& key, const float& x, const float& y, const float& radius, const std::string& text, const short& textSize = 12);
	void updateBars(const float& dt);
	void update(const float& dt, const sf::Vector2f& mousePos);
	void render(sf::RenderTarget& target);
};

