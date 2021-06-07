#include "stdafx.h"

//==================================== BUTTON ============================================
gui::Button::Button(float x, float y, float width, float height,
	sf::Font& font, std::string text, unsigned character_size,
	sf::Color text_idle_color, sf::Color text_hover_color, sf::Color text_active_color,
	sf::Color idle_color, sf::Color hover_color, sf::Color active_color,
	sf::Color outline_idle_color, sf::Color outline_hover_color, sf::Color outline_active_color,
	short unsigned id) : font(font), id(id)
{
	this->buttonState = 0;
	this->shape.setPosition(sf::Vector2f(x, y));
	this->shape.setSize(sf::Vector2f(width, height));\
	this->shape.setFillColor(this->idleColor);
	this->shape.setOutlineThickness(1.f);
	this->shape.setOutlineColor(outline_idle_color);
	
	this->text.setFont(this->font);
	this->text.setString(text);
	this->text.setFillColor(text_idle_color);
	this->text.setCharacterSize(character_size);
	this->text.setPosition(
		this->shape.getPosition().x + (this->shape.getGlobalBounds().width/2.f) - this->text.getGlobalBounds().width/2.f, 
		this->shape.getPosition().y + (this->shape.getGlobalBounds().height / 2.f) - this->text.getGlobalBounds().height / 2.f
	);

	this->TextIdleColor = text_idle_color;
	this->TextHoverColor = text_hover_color;
	this->TextActiveColor = text_active_color;

	this->idleColor = idle_color;
	this->hoverColor = hover_color;
	this->activeColor = active_color;

	this->outlineIdleColor = outline_idle_color;
	this->outlineHoverColor = outline_hover_color;
	this->outlineActiveColor = outline_active_color;
}

gui::Button::~Button()
{}

//Accesors
const std::string gui::Button::getText() const
{
	return this->text.getString();
}

const short unsigned gui::Button::getID() const
{
	return this->id;
}

//Modifiers
void gui::Button::setText(const std::string text)
{
	this->text.setString(text);
}

void gui::Button::setID(const short unsigned id)
{
	this->id = id;
}

void gui::Button::setTextColor(sf::Color idle_color, sf::Color hover_color, sf::Color active_color) 
{
	this->TextIdleColor = idle_color;
	this->TextHoverColor = hover_color;
	this->TextActiveColor = active_color;

}

void gui::Button::setBackgroundColor(sf::Color idle_color, sf::Color hover_color, sf::Color active_color)
{
	this->idleColor = idle_color; 
	this->hoverColor = hover_color;
	this->activeColor = active_color;
}

void gui::Button::setOutlineColor(sf::Color idle_color, sf::Color hover_color, sf::Color active_color) 
{
	this->outlineIdleColor = idle_color;
	this->outlineHoverColor = hover_color;
	this->outlineActiveColor = active_color;
}

//Functions
const bool gui::Button::isPressed() const
{
	if (this->buttonState == BTN_ACTIVE)
		return true;

	return false;
}

void gui::Button::update(const sf::Vector2f& mousePos)
{
	/*Update the booleans for hover, and pressed*/

	//Idle
	this->buttonState = BTN_IDLE;
	//hover
	if (this->shape.getGlobalBounds().contains(mousePos)) 
	{
		this->buttonState = BTN_HOVER;
		//
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			this->buttonState = BTN_ACTIVE;
		}
	}

	switch(this->buttonState)
	{
	case BTN_IDLE:
		this->shape.setFillColor(this->idleColor);
		this->text.setFillColor(this->TextIdleColor);
		this->shape.setOutlineColor(this->outlineIdleColor);
		break;
	case BTN_HOVER:
		this->shape.setFillColor(this->hoverColor);
		this->text.setFillColor(this->TextHoverColor);
		this->shape.setOutlineColor(this->outlineHoverColor);
		break;
	case BTN_ACTIVE:
		this->shape.setFillColor(this->activeColor);
		this->text.setFillColor(this->TextActiveColor);
		this->shape.setOutlineColor(this->outlineHoverColor);
		break;
	default:
		this->shape.setFillColor(sf::Color::Red);
		this->text.setFillColor(sf::Color::Blue);
		this->shape.setOutlineColor(sf::Color::Green);
		break;
	}

}

void gui::Button::render(sf::RenderTarget& target)
{
	target.draw(this->shape);
	target.draw(this->text);
}

//==================================== Drop Down List ============================================

gui::DropDownList::DropDownList(float x, float y, float width, float height,
	sf::Font& font, std::string list[], unsigned nrOfElements, unsigned default_index)
	: font(font), showList(false), keyTimeMax(10.f), keyTime(0.f)
{
	this->activeElement = std::make_shared<gui::Button>(
		x, y, width, height,
		this->font, list[default_index], 20,
		sf::Color(245, 255, 255, 150), sf::Color(255, 255, 255, 200), sf::Color(255, 255, 250, 50),
		sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 200), sf::Color(20, 20, 20, 200),
		sf::Color(255, 255, 255, 200), sf::Color(255, 255, 255, 255), sf::Color(255, 255, 255, 50)
		);

	//unsigned nrOfElements = sizeof(list) / sizeof(std::string);
	//Goes through number of elements wanted and adds them
	for (short unsigned i = 0; i < nrOfElements; i++) {
		
		this->list.push_back(std::make_shared<gui::Button>(
			x, y+(height * (i+1)), width, height,
			this->font, list[i], 20,
			sf::Color(245, 255, 255, 250), sf::Color(255, 255, 255, 255), sf::Color(255, 255, 250, 50),
			sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 200), sf::Color(20, 20, 20, 200),
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
	if (this->keyTime > this->keyTimeMax)
	{
		this->keyTime = 0.f;
		return true;
	}
	return false;
}

const unsigned short gui::DropDownList::getActiveID() const
{
	return this->activeElement->getID();
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
	
	this->updateKeyTime(dt);
	this->activeElement->update(mousePos);
	if (this->activeElement->isPressed() && this->getKeyTime()) {
		if(showList)
		this->showList = true;
		else
		this->showList = true;
	}
	if (this->showList) {
		for (auto& i : this->list)
		{
			i->update(mousePos);
			if (i->isPressed() && this->getKeyTime()) {
				this->activeElement->setText(i->getText());
				this->showList = false;
				this->activeElement->setID(i->getID());
			}

		}
	}
	this->activeElement->update(mousePos);
}

void gui::DropDownList::render(sf::RenderTarget& target)
{
	this->activeElement->render(target);

	if (this->showList)
	{
		for (auto& i : this->list)
		{
			i->render(target);
		}
	}
}

//==================================== Texture Selector ============================================

gui::TextureSelector::TextureSelector(float x, float y, float width, float height, float gridSize, const sf::Texture& texture_sheet, sf::Font& font)
	: active(false), hidden(false),gridSize(gridSize), font(font), keyTimeMax(10.f), keyTime(0.f)
{
	//bounds initialization
	this->bounds.setSize(sf::Vector2f(width, height));
	this->bounds.setPosition(x, y);
	this->bounds.setFillColor(sf::Color(50, 50, 50, 100));
	this->bounds.setOutlineThickness(1.f);
	this->bounds.setOutlineColor(sf::Color(255, 255, 255, 200));
	
	this->sheet.setTexture(texture_sheet);
	this->sheet.setPosition(x, y);

	if (this->sheet.getGlobalBounds().width > width) {
		this->sheet.setTextureRect(sf::IntRect(0, 0, (int)width, (int)this->sheet.getGlobalBounds().height));
	}
	// did width and height variables instead of this->bounds.getGlobalBounds().width 
	//so it doesn't have to run all those functions
	if (this->sheet.getGlobalBounds().height > height) {
		this->sheet.setTextureRect(sf::IntRect(0, 0, (int)this->sheet.getGlobalBounds().width, (int)height));
	}

	this->selector.setPosition(x, y);
	this->selector.setSize(sf::Vector2f(gridSize, gridSize));
	this->selector.setFillColor(sf::Color::Transparent);
	this->selector.setOutlineThickness(1.f);
	this->selector.setOutlineColor(sf::Color::Red);

	this->textureRect.width = (int)gridSize;
	this->textureRect.height = (int)gridSize;

	this->hideButton = std::make_unique<gui::Button>(
		x, y, 20.f, 20.f,
		this->font, "", 1,
		sf::Color(255, 255, 255, 150), sf::Color(255, 255, 255, 150), sf::Color(255, 255, 250, 150),
		sf::Color(150, 150, 150, 200), sf::Color(100, 100, 100, 200), sf::Color(60, 60, 60, 200),
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
	if (this->keyTime > this->keyTimeMax)
	{
		this->keyTime = 0.f;
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
	this->updateKeyTime(dt);
	this->hideButton->update(mousePosWindow);

	if (this->hideButton->isPressed() && this->getKeyTime())
	{
		if (this->hidden)
			hidden = false;
		else {
			hidden = true;
			active = false;
		}
	}

	if (!this->hidden) {
		if (this->bounds.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosWindow)))
			this->active = true;
		else
			this->active = false;

		if (this->active)
		{
			this->mousePosGrid = sf::Vector2u((unsigned)mousePosWindow.x / (unsigned)gridSize, (unsigned)mousePosWindow.y / (unsigned)gridSize);
			this->selector.setPosition(
				(this->mousePosGrid.x * gridSize) + this->bounds.getPosition().x,
				(this->mousePosGrid.y * gridSize) + this->bounds.getPosition().y
			);
		}
		this->textureRect.left = (int)this->selector.getPosition().x - (int)this->bounds.getPosition().x;
		this->textureRect.top = (int)this->selector.getPosition().y - (int)this->bounds.getPosition().y;
	}
}

void gui::TextureSelector::move(const bool right)
{

	if (right) {
		//if(this->sheet.getTextureRect().left + this->sheet.getGlobalBounds().width >= this->bounds.getTextureRect().left + this->bounds.getGlobalBounds().width)
			this->sheet.setTextureRect(sf::IntRect((int)this->getTextureRect().left + (int)gridSize, 0, (int)this->sheet.getGlobalBounds().width, (int)this->sheet.getGlobalBounds().height));
	}
	else {
			//if(this->sheet.getTextureRect().left > 0)
				this->sheet.setTextureRect(sf::IntRect((int)this->getTextureRect().left - (int)gridSize, 0, (int)this->sheet.getGlobalBounds().width, (int)this->sheet.getGlobalBounds().height));
		}
}


void gui::TextureSelector::render(sf::RenderTarget& target)
{
	
	if (!this->hidden) {
		target.draw(this->bounds);
		target.draw(this->sheet);
		if (this->active)
			target.draw(this->selector);
	}
	this->hideButton->render(target);
}

const bool& gui::TextureSelector::getActive() const
{
	return this->active;
}
