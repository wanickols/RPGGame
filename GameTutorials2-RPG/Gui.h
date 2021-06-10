#pragma once

namespace sf {
	class Texture;
	class Sprite;
	class RenderTarget;
	class Font;
	class Color;
	class RectangleShape;
}

enum button_states { BTN_IDLE = 0, BTN_HOVER, BTN_ACTIVE };

namespace gui {

	class Button
	{
	public:
		Button(float x, float t, float width, float height,
			sf::Font& font, std::string text, unsigned character_size,
			sf::Color text_idle_color, sf::Color text_hover_color, sf::Color text_active_color,
			sf::Color idle_color, sf::Color hover_color, sf::Color active_color,
			sf::Color outline_idle_color = sf::Color::Transparent, sf::Color outline_hover_color = sf::Color::Transparent, sf::Color outline_active_color = sf::Color::Transparent,
			short unsigned id = 0);
		virtual ~Button();

		//Acessors
		const bool isPressed() const;
		const std::string getText() const;
		const short unsigned getID() const;

		//Modifiers
		void setText(const std::string text);
		void setID(const short unsigned id);
		void setTextColor(sf::Color idle_color, sf::Color hover_color, sf::Color active_color); //Put these so can adjust color without full constructor necessary
		void setBackgroundColor(sf::Color idle_color, sf::Color hover_color, sf::Color active_color);
		void setOutlineColor(sf::Color idle_color, sf::Color hover_color, sf::Color active_color);

		//Functions
		void update(const sf::Vector2f& mousePos);
		void render(sf::RenderTarget& target);



	private:
		short unsigned buttonState;
		short unsigned id;

		sf::RectangleShape shape; //basic shape of button
		sf::Font& font;
		sf::Text text;

		//colors
		sf::Color TextIdleColor;
		sf::Color TextHoverColor;
		sf::Color TextActiveColor;

		sf::Color idleColor;
		sf::Color hoverColor;
		sf::Color activeColor;

		sf::Color outlineIdleColor;
		sf::Color outlineHoverColor;
		sf::Color outlineActiveColor;
	};

	class DropDownList
	{
	public:
		DropDownList(float x, float y, float width, float height,
			sf::Font& font, std::string list[], unsigned nrOfElements, unsigned default_index = 0);
		~DropDownList();

		//Accessors
		const unsigned short getActiveID() const;

		//Functions
		const bool getKeyTime();
		void updateKeyTime(const float& dt);
		void update(const sf::Vector2f& mousePos, const float& dt);
		void render(sf::RenderTarget& target);
	private:
		sf::Font& font;
		float keyTime;
		float keyTimeMax;
		bool showList;
		std::shared_ptr<gui::Button> activeElement;
		std::vector<std::shared_ptr<gui::Button>> list;
	};

	class TextureSelector
	{
	private:
		sf::RectangleShape bounds;
		sf::Sprite sheet;
		sf::RectangleShape selector;
		sf::Vector2u mousePosGrid;
		sf::IntRect textureRect;
		float gridSize;
		bool active;
		bool hidden;
		float keyTime;
		float keyTimeMax;
		std::unique_ptr<Button> hideButton;
		sf::Font& font;



	public:
		TextureSelector(float x, float y, float width, float height, float gridSize, const sf::Texture& texture_sheet, sf::Font& font);
		~TextureSelector();

		//Accessors
		const bool& getActive() const;
		const sf::IntRect& getTextureRect() const;

		//Functions
		void move(const bool rightorleft);
		const bool getKeyTime();
		void updateKeyTime(const float& dt);
		void update(const sf::Vector2f& mousePosWindow, const float& dt);
		void render(sf::RenderTarget& target);
	};
}
