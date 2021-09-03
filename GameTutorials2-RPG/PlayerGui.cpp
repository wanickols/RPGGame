#include "stdafx.h"
#include "Player.h"
#include "PlayerGui.h"

progressBar::progressBar(float frontWidth, float backWidth, float height, float xPos, float yPos, sf::Color backgroundColor, sf::Color fillColor, std::shared_ptr<Player>& player, sf::Font& font,int offset, int fontSize)
	: fullWidth(frontWidth), percentWidth(100), height(height), player(player)
{
	this->text.setFont(font);
	this->text.setCharacterSize(fontSize);
	this->text.setFillColor(sf::Color(250,250,250,230));
	this->text.setPosition(xPos + (float)fontSize/3 + (float)offset*2, yPos + (height/2) - ((float)fontSize/3));
	this->text.setString("HP:" + 100);
	
	this->ProgBarBack.setSize(sf::Vector2f(backWidth, height));
	this->ProgBarBack.setFillColor(backgroundColor);
	this->ProgBarBack.setPosition(xPos, yPos);
	this->ProgBarBack.setOutlineColor(sf::Color(255,255,255,250));
	this->ProgBarBack.setOutlineThickness(3.f);

	this->ProgBarIn.setSize(sf::Vector2f(frontWidth, height));
	this->ProgBarIn.setFillColor(fillColor);
	this->ProgBarIn.setPosition(xPos + offset, yPos);
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
	addButton("LEVEL", 50.f, 50.f, 40.f, std::to_string(this->player->getAttributeComponent()->level), 40);
}

void PlayerGui::initBars()
{
												//Front width, bckwdth, height, xpos, ypos, backcolor, fillcolor, player, font, (optional)fontsize
	this->HPBar = std::make_unique<progressBar>(230.f, 250.f, 45.f, 50.f, 10.f, sf::Color(50, 50, 50, 200), sf::Color(250,20,20,210), this->player, this->font, 20);
	this->ExpBar = std::make_unique<progressBar>(210.f, 210.f, 12.f, 90.f, 60.f, sf::Color(50, 50, 50, 200), sf::Color(140, 140, 140, 250), this->player, this->font, 0, 10);
}

PlayerGui::PlayerGui(std::shared_ptr<Player> player, sf::Font& font)
	: player(player), font(font)
{
	this->initLevel();
	this->initBars();
}

void PlayerGui::addButton(const std::string& key, const float& x, const float& y, const float& width, const float& height, const std::string& text, const short& textSize)
{
	this->buttons[key] = std::make_unique<gui::Button>(x, y, width, height,
		this->font, text, textSize,
		sf::Color(245, 212, 0, 250), sf::Color(255, 222, 0, 255), sf::Color(0, 0, 250, 50),
		sf::Color(70, 70, 70, 255), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 255), gui::button_types::RECTANGLE
		);
}

void PlayerGui::addButton(const std::string& key, const float& x, const float& y, const float& radius, const std::string& text, const short& textSize)
{
	this->buttons[key] = std::make_unique<gui::Button>(x, y, radius, radius,
		this->font, text, textSize,
		sf::Color(255, 255, 255, 245), sf::Color(255, 255, 255, 255), sf::Color(250, 250, 250, 250),
		sf::Color(120, 120, 120, 255), sf::Color(150, 150, 150, 255), sf::Color(100, 100, 100, 255), gui::button_types::CIRCLE, 3.f
		, sf::Color(255, 255, 255, 250), sf::Color(230,230,230,235)
		);
}

void PlayerGui::updateBars(const float& dt)
{
	if (this->player->getAttributeComponent()->healthUpdate) {
		HPBarText = "HP: " + std::to_string(this->player->getAttributeComponent()->hp) + " / " + std::to_string(this->player->getAttributeComponent()->hpMax);
		tempPercent = (float)player->getAttributeComponent()->hp / (float)player->getAttributeComponent()->hpMax;
		HPBar->update(dt, tempPercent, HPBarText);
	this->player->getAttributeComponent()->healthUpdate = false;
	}
	if (this->player->getAttributeComponent()->expUpdate) {
		ExpBarText = "EXP: " + std::to_string(this->player->getAttributeComponent()->exp) + " / " + std::to_string(this->player->getAttributeComponent()->expnext);
		tempPercent = (float)player->getAttributeComponent()->exp / (float)player->getAttributeComponent()->expnext;;
		ExpBar->update(dt, tempPercent, ExpBarText);
		this->player->getAttributeComponent()->expUpdate = false;
	}
}

//Functions
void PlayerGui::update(const float& dt, const sf::Vector2f& mousePos)
{

	this->updateBars(dt);
		
	
		for (auto& i : this->buttons)
		{
			i.second->update(mousePos);
			if (i.first == "LEVEL") {
				if (this->player->getAttributeComponent()->levelUpdate) {
					i.second->setText(std::to_string(this->player->getAttributeComponent()->level));
					this->player->getAttributeComponent()->levelUpdate = false;
				}
			}
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


