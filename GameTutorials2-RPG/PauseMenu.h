#pragma once

namespace sf
{
	class Font;
	class Text;
	class RectangleShape;
	class RenderTarget;
}

namespace gui {
	class Button;
}

class PauseMenu
{
public:
	sf::Font& font;
	sf::Text menuText;


	PauseMenu(sf::RenderWindow& window, sf::Font& font, float button_width, float button_height, int character_size);
	virtual ~PauseMenu();

	//Accessors
	std::map <std::string, std::unique_ptr<gui::Button>>& getButtons();

	//Functions
	const bool isButtonPressed(const std::string key);
	void addButton(const std::string key, float y, const std::string text);
	void update(const float& dt, const sf::Vector2f& mousePos);
	void render(sf::RenderTarget& target);
private:
	sf::RectangleShape background;
	sf::RectangleShape container;

	std::map < std::string, std::unique_ptr<gui::Button>> buttons;
	float buttonWidth;
	float buttonHeight;
	int characterSize;

	//Functions

};

