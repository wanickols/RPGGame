#include "stdafx.h"
#include "Player.h"
#include "PlayerGui.h"

progressBar::progressBar(float frontWidth, float backWidth, float height, float xPos, float yPos, sf::Color backgroundColor, sf::Color fillColor, std::shared_ptr<Player>& player, sf::Font& font, int fontSize)
	: fullWidth(backWidth), percentWidth(100), height(height), player(player)
{
	this->text.setFont(font);
	this->text.setCharacterSize(fontSize);
	this->text.setFillColor(sf::Color(250,250,250,230));
	this->text.setPosition(xPos + (float)fontSize/3, yPos + (height/2) - ((float)fontSize/3));
	this->text.setString("HP:" + 100);
	
	this->ProgBarBack.setSize(sf::Vector2f(backWidth + height/4, height + height/4));
	this->ProgBarBack.setFillColor(backgroundColor);
	this->ProgBarBack.setPosition(xPos, yPos);

	this->ProgBarIn.setSize(sf::Vector2f(frontWidth, height));
	this->ProgBarIn.setFillColor(fillColor);
	this->ProgBarIn.setPosition(xPos+ height/8, yPos+ height/8);
}

void progressBar::update(const float& dt, float& percentWidth)
{
	this->ProgBarIn.setSize(sf::Vector2f((float)std::floor(percentWidth * fullWidth), height));
	this->ProgBarIn.setSize(sf::Vector2f((float)std::floor(percentWidth * fullWidth), height));
}

void progressBar::update(const float& dt, float& percentWidth, std::string textString)
{

	this->update(dt, percentWidth);
	this->text.setString(textString);
}

void progressBar::render(sf::RenderTarget& target)
{
	target.draw(this->ProgBarBack);
	target.draw(this->ProgBarIn);
	target.draw(this->text);
}

void PlayerGui::initLevel()
{
	addButton("LEVEL", 50.f, 50.f, "Level" + this->player->getAttributeComponent()->level);
}

void PlayerGui::initBars()
{
	this->HPBar = std::make_unique<progressBar>(250.f, 250.f, 25.f, 20.f, 20.f, sf::Color(50, 50, 50, 200), sf::Color(250,20,20,210), this->player, this->font);
	this->ExpBar = std::make_unique<progressBar>(200.f, 200.f, 10.f, 20.f, 60.f, sf::Color(50, 50, 50, 200), sf::Color(140, 140, 140, 250), this->player, this->font, 10);
}

PlayerGui::PlayerGui(std::shared_ptr<Player> player, sf::Font& font)
	: player(player), font(font)
{
	this->initLevel();
	this->initBars();
}

void PlayerGui::addButton(const std::string& key, const float& x, const float& y, const std::string& text)
{
	float width = 25.f;
	float height = 25.f;
	this->buttons[key] = std::make_unique<gui::Button>(x, y, width, height,
		this->font, text, 13,
		sf::Color(245, 212, 0, 250), sf::Color(255, 222, 0, 255), sf::Color(0, 0, 250, 50),
		sf::Color(70, 70, 70, 255), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 255), gui::button_types::CIRCLE
		);
}

void PlayerGui::updateBars(const float& dt)
{
	HPBarText = "HP: " + std::to_string(this->player->getAttributeComponent()->hp) + " / " + std::to_string(this->player->getAttributeComponent()->hpMax);
	tempPercent = (float)player->getAttributeComponent()->hp / (float)player->getAttributeComponent()->hpMax;
	HPBar->update(dt, tempPercent, HPBarText);

	ExpBarText = "EXP: " + std::to_string(this->player->getAttributeComponent()->exp) + " / " + std::to_string(this->player->getAttributeComponent()->expnext);
	tempPercent = (float)player->getAttributeComponent()->exp / (float)player->getAttributeComponent()->expnext;;
	ExpBar->update(dt, tempPercent, ExpBarText);
}

//Functions
void PlayerGui::update(const float& dt, const sf::Vector2f& mousePos)
{
	this->updateBars(dt);
	for (auto& i : this->buttons)
	{
		i.second->update(mousePos);
	}
}

void PlayerGui::render(sf::RenderTarget& target)
{
	HPBar->render(target);
	ExpBar->render(target);
	for (auto& i : this->buttons)
	{
		i.second->render(target);
	}
}


