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

void progressBar::update(const float& dt, float percentWidth, std::string textString)
{

	this->ProgBarIn.setSize(sf::Vector2f((float)std::floor(percentWidth * fullWidth), height));
	this->ProgBarIn.setSize(sf::Vector2f((float)std::floor(percentWidth * fullWidth), height));
	
	if(textString != "N")
		this->text.setString(textString);
}

void progressBar::render(sf::RenderTarget& target)
{
	target.draw(this->ProgBarBack);
	target.draw(this->ProgBarIn);
	target.draw(this->text);
}

void PlayerGui::initBars(sf::Font& font)
{
	this->HPBar = std::make_unique<progressBar>(250.f, 250.f, 25.f, 20.f, 20.f, sf::Color(50, 50, 50, 200), sf::Color(250,20,20,210), this->player, font);
	this->ExpBar = std::make_unique<progressBar>(200.f, 200.f, 10.f, 20.f, 60.f, sf::Color(50, 50, 50, 200), sf::Color(140, 140, 140, 250), this->player, font, 10);
}

PlayerGui::PlayerGui(std::shared_ptr<Player> player, sf::Font& font)
	: player(player)
{
	this->initBars(font);
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
void PlayerGui::update(const float& dt)
{
	this->updateBars(dt);
}

void PlayerGui::render(sf::RenderTarget& target)
{
	HPBar->render(target);
	ExpBar->render(target);
}


