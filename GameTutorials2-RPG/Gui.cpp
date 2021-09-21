#include "stdafx.h"
#include "Player.h"
/*
*
*
*==================================== Gui ============================================
*
*/

const float gui::p2pX(const float& perc, sf::VideoMode& vm)
{
	return std::floor(static_cast<float>(vm.width) * (perc / 100.f));
}

const float gui::p2pY(const float& perc, sf::VideoMode& vm)
{
	return std::floor(static_cast<float>(vm.height) * (perc / 100.f));
}

const float gui::p2pS(const float& perc, sf::VideoMode& vm)
{
	return std::floor(static_cast<float>(vm.height+ vm.width) * (perc / 100.f));;
}


/*
*
*
*==================================== BUTTON ============================================
*
*/

gui::Button::Button(float x, float y, float width, float height,
	sf::Font& font, std::string text, short character_size,
	sf::Color text_idle_color, sf::Color text_hover_color, sf::Color text_active_color,
	sf::Color idle_color, sf::Color hover_color, sf::Color active_color,
	gui::button_types type, float outline_thickness,
	sf::Color outline_idle_color, sf::Color outline_hover_color, sf::Color outline_active_color,
	short unsigned id) : font(font), id(id), width(width)
{

	shapes.reserve(1);

	buttonState = 0;

	this->text.setFont(font);
	this->text.setString(text);
	this->text.setFillColor(text_idle_color);
	this->text.setCharacterSize(character_size);
	
	switch (type)
	{
	case(gui::button_types::RECTANGLE):
	{
		
		std::unique_ptr<sf::RectangleShape> rect = std::make_unique<sf::RectangleShape>(); // had to do because shape has no setSize. Found no way around it
		rect->setSize(sf::Vector2f(width, height));
		shapes.emplace_back(std::move(rect));
		shapes.back().get()->setPosition((sf::Vector2f(x, y)));

		this->text.setPosition(
			shapes.back()->getPosition().x + (shapes.back()->getGlobalBounds().width / 2.f) - this->text.getGlobalBounds().width / 2.f,
			shapes.back()->getPosition().y + (shapes.back()->getGlobalBounds().height / 2.f) - this->text.getGlobalBounds().height / 2.f
		);
		break;
	}
	case(gui::button_types::CIRCLE):
	{
		
		std::unique_ptr<sf::CircleShape> circle = std::make_unique<sf::CircleShape>();
		circle->setRadius(width);
		shapes.emplace_back(std::move(circle));
		shapes.back().get()->setPosition((sf::Vector2f(x - width, y - width)));
		this->text.setPosition(
			shapes.back()->getPosition().x + width - this->text.getGlobalBounds().width - this->text.getScale().x*2.f,
			shapes.back()->getPosition().y + width - this->text.getGlobalBounds().height
		);
	}
	break;
	case(gui::button_types::CONVEX):
	{
	
		std::unique_ptr<sf::ConvexShape> convex = std::make_unique<sf::ConvexShape>();
		convex->setPointCount(3);//
		shapes.emplace_back(std::move(convex));
		shapes.back().get()->setPosition((sf::Vector2f(x, y)));
		this->text.setPosition(
			shapes.back()->getPosition().x + (shapes.back()->getGlobalBounds().width / 2.f) - this->text.getGlobalBounds().width / 2.f,
			shapes.back()->getPosition().y + (shapes.back()->getGlobalBounds().height / 2.f) - this->text.getGlobalBounds().height / 2.f
		);
	}
	break;
	default:
		std::cout << "ERROR::GUI : BUTTON TYPE NOT FOUND" << std::endl;
		break;
	
	}


	shapes.back()->setFillColor(idleColor);
	shapes.back()->setOutlineThickness(outline_thickness);
	shapes.back()->setOutlineColor(outline_idle_color);



	TextIdleColor = text_idle_color;
	TextHoverColor = text_hover_color;
	TextActiveColor = text_active_color;

	idleColor = idle_color;
	hoverColor = hover_color;
	activeColor = active_color;

	outlineIdleColor = outline_idle_color;
	outlineHoverColor = outline_hover_color;
	outlineActiveColor = outline_active_color;
}


gui::Button::~Button()
{}

//Accesors
const std::string gui::Button::getText() const
{
	return text.getString();
}

const short unsigned gui::Button::getID() const
{
	return id;
}

//Modifiers
void gui::Button::setText(const std::string text)
{
	this->text.setString(text);
	this->text.setPosition(
		shapes.back()->getPosition().x + width - this->text.getGlobalBounds().width/2,
		shapes.back()->getPosition().y + width - this->text.getGlobalBounds().height *.9f
	);
}

void gui::Button::setID(const short unsigned id)
{
	this->id = id;
}

void gui::Button::setTextColor(sf::Color idle_color, sf::Color hover_color, sf::Color active_color)
{
	TextIdleColor = idle_color;
	TextHoverColor = hover_color;
	TextActiveColor = active_color;

}

void gui::Button::setBackgroundColor(sf::Color idle_color, sf::Color hover_color, sf::Color active_color)
{
	idleColor = idle_color;
	hoverColor = hover_color;
	activeColor = active_color;
}

void gui::Button::setOutlineColor(sf::Color idle_color, sf::Color hover_color, sf::Color active_color)
{
	outlineIdleColor = idle_color;
	outlineHoverColor = hover_color;
	outlineActiveColor = active_color;
}

//Functions
const bool gui::Button::isPressed() const
{
	if (buttonState == BTN_ACTIVE)
		return true;

	return false;
}

void gui::Button::update(const sf::Vector2f& mousePos)
{
	/*Update the booleans for hover, and pressed*/

	//Idle
	buttonState = BTN_IDLE;
	//hover
	if (shapes.back()->getGlobalBounds().contains(mousePos))
	{
		buttonState = BTN_HOVER;
		//
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			buttonState = BTN_ACTIVE;
		}
	}

	switch (buttonState)
	{
	case BTN_IDLE:
		shapes.back()->setFillColor(idleColor);
		text.setFillColor(TextIdleColor);
		shapes.back()->setOutlineColor(outlineIdleColor);
		break;
	case BTN_HOVER:
		shapes.back()->setFillColor(hoverColor);
		text.setFillColor(TextHoverColor);
		shapes.back()->setOutlineColor(outlineHoverColor);
		break;
	case BTN_ACTIVE:
		shapes.back()->setFillColor(activeColor);
		text.setFillColor(TextActiveColor);
		shapes.back()->setOutlineColor(outlineHoverColor);
		break;
	default:
		shapes.back()->setFillColor(sf::Color::Red);
		text.setFillColor(sf::Color::Blue);
		shapes.back()->setOutlineColor(sf::Color::Green);
		break;
	}

}

void gui::Button::render(sf::RenderTarget& target)
{
	target.draw(*shapes.back());
	target.draw(text);
}

/*
*
*==================================== Drop Down List ============================================
*
*/

gui::DropDownList::DropDownList(float x, float y, float width, float height,
	sf::Font& font, std::string list[], unsigned nrOfElements, unsigned default_index)
	: font(font), showList(false), keyTimeMax(10.f), keyTime(0.f)
{
	activeElement = std::make_shared<gui::Button>(
		x, y, width, height,
		font, list[default_index], 20,
		sf::Color(245, 255, 255, 150), sf::Color(255, 255, 255, 200), sf::Color(255, 255, 250, 50),
		sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 200), sf::Color(20, 20, 20, 200), gui::button_types::RECTANGLE, 1.f,
		sf::Color(255, 255, 255, 200), sf::Color(255, 255, 255, 255), sf::Color(255, 255, 255, 50)
		);

	//unsigned nrOfElements = sizeof(list) / sizeof(std::string);
	//Goes through number of elements wanted and adds them
	for (short unsigned i = 0; i < nrOfElements; i++) {

		this->list.push_back(std::make_shared<gui::Button>(
			x, y + (height * (i + 1)), width, height,
			font, list[i], 20,
			sf::Color(245, 255, 255, 250), sf::Color(255, 255, 255, 255), sf::Color(255, 255, 250, 50),
			sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 200), sf::Color(20, 20, 20, 200), gui::button_types::RECTANGLE, 1.f,
			sf::Color(255, 255, 255, 255), sf::Color(255, 255, 255, 255), sf::Color(255, 255, 255, 255),
			i
			));

	}
}

gui::DropDownList::~DropDownList()
{
}

//Accessors
const bool gui::DropDownList::getKeyTime()
{
	if (keyTime > keyTimeMax)
	{
		keyTime = 0.f;
		return true;
	}
	return false;
}

const unsigned short gui::DropDownList::getActiveID() const
{
	return activeElement->getID();
}

//Functions
void gui::DropDownList::updateKeyTime(const float& dt)
{
	if (keyTime < keyTimeMax) {
		keyTime += 100.f * dt;
	}
}

void gui::DropDownList::update(const sf::Vector2f& mousePos, const float& dt)
{

	updateKeyTime(dt);
	activeElement->update(mousePos);
	if (activeElement->isPressed() && getKeyTime()) {
		if (showList)
			showList = true;
		else
			showList = true;
	}
	if (showList) {
		for (auto& i : list)
		{
			i->update(mousePos);
			if (i->isPressed() && getKeyTime()) {
				activeElement->setText(i->getText());
				showList = false;
				activeElement->setID(i->getID());
			}

		}
	}
	activeElement->update(mousePos);
}

void gui::DropDownList::render(sf::RenderTarget& target)
{
	activeElement->render(target);

	if (showList)
	{
		for (auto& i : list)
		{
			i->render(target);
		}
	}
}

/*
* 
* 
*==================================== Texture Selector ============================================
*
*/

gui::TextureSelector::TextureSelector(float x, float y, float width, float height, float gridSize, const sf::Texture& texture_sheet, sf::Font& font)
	: active(false), hidden(false), gridSize(gridSize), font(font), keyTimeMax(10.f), keyTime(0.f)
{
	//bounds initialization
	bounds.setSize(sf::Vector2f(width, height));
	bounds.setPosition(x, y);
	bounds.setFillColor(sf::Color(50, 50, 50, 100));
	bounds.setOutlineThickness(1.f);
	bounds.setOutlineColor(sf::Color(255, 255, 255, 200));

	sheet.setTexture(texture_sheet);
	sheet.setPosition(x, y);

	if (sheet.getGlobalBounds().width > width) {
		sheet.setTextureRect(sf::IntRect(0, 0, (int)width, (int)sheet.getGlobalBounds().height));
	}
	// did width and height variables instead of bounds.getGlobalBounds().width 
	//so it doesn't have to run all those functions
	if (sheet.getGlobalBounds().height > height) {
		sheet.setTextureRect(sf::IntRect(0, 0, (int)sheet.getGlobalBounds().width, (int)height));
	}

	selector.setPosition(x, y);
	selector.setSize(sf::Vector2f(gridSize, gridSize));
	selector.setFillColor(sf::Color::Transparent);
	selector.setOutlineThickness(1.f);
	selector.setOutlineColor(sf::Color::Red);

	textureRect.width = (int)gridSize;
	textureRect.height = (int)gridSize;

	hideButton = std::make_unique<gui::Button>(
		x, y, 20.f, 20.f,
		font, "", 1,
		sf::Color(255, 255, 255, 150), sf::Color(255, 255, 255, 150), sf::Color(255, 255, 250, 150),
		sf::Color(150, 150, 150, 200), sf::Color(100, 100, 100, 200), sf::Color(60, 60, 60, 200),
		gui::button_types::RECTANGLE, 1.f,
		sf::Color(255, 255, 255, 255), sf::Color(255, 255, 255, 255), sf::Color(255, 255, 255, 255)
		);
}

gui::TextureSelector::~TextureSelector()
{
}

const sf::IntRect& gui::TextureSelector::getTextureRect() const
{
	return textureRect;
}

//Functions
const bool gui::TextureSelector::getKeyTime()
{
	if (keyTime > keyTimeMax)
	{
		keyTime = 0.f;
		return true;
	}
	return false;
}

void gui::TextureSelector::updateKeyTime(const float& dt)
{
	if (keyTime < keyTimeMax) {
		keyTime += 100.f * dt;
	}
}

void gui::TextureSelector::update(const sf::Vector2f& mousePosWindow, const float& dt)
{
	updateKeyTime(dt);
	hideButton->update(mousePosWindow);

	if (hideButton->isPressed() && getKeyTime())
	{
		if (hidden)
			hidden = false;
		else {
			hidden = true;
			active = false;
		}
	}

	if (!hidden) {
		if (bounds.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosWindow)))
			active = true;
		else
			active = false;

		if (active)
		{
			mousePosGrid = sf::Vector2u((unsigned)mousePosWindow.x / (unsigned)gridSize, (unsigned)mousePosWindow.y / (unsigned)gridSize);
			selector.setPosition(
				(mousePosGrid.x * gridSize) + bounds.getPosition().x,
				(mousePosGrid.y * gridSize) + bounds.getPosition().y
			);
		}
		textureRect.left = (int)selector.getPosition().x - (int)bounds.getPosition().x;
		textureRect.top = (int)selector.getPosition().y - (int)bounds.getPosition().y;
	}
}

void gui::TextureSelector::move(const bool right)
{

	if (right) {
		//if(sheet.getTextureRect().left + sheet.getGlobalBounds().width >= bounds.getTextureRect().left + bounds.getGlobalBounds().width)
		sheet.setTextureRect(sf::IntRect((int)getTextureRect().left + (int)gridSize, 0, (int)sheet.getGlobalBounds().width, (int)sheet.getGlobalBounds().height));
	}
	else {
		//if(sheet.getTextureRect().left > 0)
		sheet.setTextureRect(sf::IntRect((int)getTextureRect().left - (int)gridSize, 0, (int)sheet.getGlobalBounds().width, (int)sheet.getGlobalBounds().height));
	}
}


void gui::TextureSelector::render(sf::RenderTarget& target)
{

	if (!hidden) {
		target.draw(bounds);
		target.draw(sheet);
		if (active)
			target.draw(selector);
	}
	hideButton->render(target);
}

const bool& gui::TextureSelector::getActive() const
{
	return active;
}

//Progress Bar
gui::progressBar::progressBar(float frontWidth, float backWidth, float height, float xPos, float yPos, sf::Color backgroundColor, sf::Color fillColor, std::shared_ptr<Player>& player, sf::Font& font, sf::VideoMode& vm, int offset, int fontSize)
	: fullWidth(frontWidth), percentWidth(100), height(height), player(player)
{
	text.setFont(font);
	text.setCharacterSize(fontSize);
	text.setFillColor(sf::Color(250, 250, 250, 230));
	text.setPosition(xPos + (float)fontSize / 2 + (float)offset * 2, yPos + (height / 2) - ((float)fontSize / 2));
	text.setString("HP:" + 100);

	ProgBarBack.setSize(sf::Vector2f(backWidth, height));
	ProgBarBack.setFillColor(backgroundColor);
	ProgBarBack.setPosition(xPos, yPos);
	ProgBarBack.setOutlineColor(sf::Color(255, 255, 255, 250));
	ProgBarBack.setOutlineThickness(gui::p2pS(0.1f, vm));

	ProgBarIn.setSize(sf::Vector2f(frontWidth, height));
	ProgBarIn.setFillColor(fillColor);
	ProgBarIn.setPosition(xPos, yPos);
}

void gui::progressBar::update(const float& dt, float& percentWidth)
{
	ProgBarIn.setSize(sf::Vector2f((float)std::floor(percentWidth * fullWidth), height));
	ProgBarIn.setSize(sf::Vector2f((float)std::floor(percentWidth * fullWidth), height));
}

void gui::progressBar::update(const float& dt, float& percentWidth, std::string textString)
{

	update(dt, percentWidth);
	text.setString(textString);
}

void gui::progressBar::render(sf::RenderTarget& target)
{
	target.draw(ProgBarBack);
	target.draw(ProgBarIn);
	target.draw(text);
}