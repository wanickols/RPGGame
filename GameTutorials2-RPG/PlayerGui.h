#pragma once

class Player;
class gui::Button;
class gui::progressBar;


class PlayerGui
{
private:
	//Init Functions
	void initLevel();
	void initBars();

public:
	PlayerGui(std::shared_ptr<Entity> player, sf::Font& font, sf::VideoMode& vm);

	//Functions
	void addButton(const std::string& key, const float& x, const float& y, const float& width, const float& height, const std::string& text, const short& textSize = 12);
	void addButton(const std::string& key, const float& x, const float& y, const float& radius, const std::string& text, const short& textSize = 12);
	void addBar
	(
		std::string key,
		float frontWidth, float backWidth, float height, float xPos, float yPos,
		sf::Color backgroundColor, sf::Color fillColor, std::shared_ptr<Entity>& player,
		sf::Font& font, sf::VideoMode& vm, int offset = 0, int fontSize = 12
	);
	void updateBars(const float& dt);
	void update(const float& dt, const sf::Vector2f& mousePos);
	void render(sf::RenderTarget& target);
	
private:
	std::shared_ptr<Entity> player;


	//variables
	float tempPercent;
	std::map < std::string, std::unique_ptr<gui::Button>> buttons; //buttons
	std::map < std::string, std::unique_ptr<gui::progressBar>> bars; //progress bars
	std::string ProgressBarText; //words that go into progressBars
	sf::Font& font;
	sf::VideoMode& vm;


	
	

};

