#include "stdafx.h"
#include "Player.h"
#include "PlayerGui.h"

progressBar::progressBar(float frontWidth, float backWidth, float height, float xPos, float yPos, sf::Color backgroundColor, sf::Color fillColor, std::shared_ptr<Player>& player, sf::Font& font, sf::VideoMode& vm, int offset, int fontSize)
	: fullWidth(frontWidth), percentWidth(100), height(height), player(player)
{
	this->text.setFont(font);
	this->text.setCharacterSize(fontSize);
	this->text.setFillColor(sf::Color(250,250,250,230));
	this->text.setPosition(xPos + (float)fontSize/2 + (float)offset*2, yPos + (height/2) - ((float)fontSize/2));
	this->text.setString("HP:" + 100);
	
	this->ProgBarBack.setSize(sf::Vector2f(backWidth, height));
	this->ProgBarBack.setFillColor(backgroundColor);
	this->ProgBarBack.setPosition(xPos, yPos);
	this->ProgBarBack.setOutlineColor(sf::Color(255,255,255,250));
	this->ProgBarBack.setOutlineThickness(gui::p2pS(0.1f, vm));

	this->ProgBarIn.setSize(sf::Vector2f(frontWidth, height));
	this->ProgBarIn.setFillColor(fillColor);
	this->ProgBarIn.setPosition(xPos, yPos);
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
	addButton("LEVEL", gui::p2pX(2.6f, vm), gui::p2pY(4.6f, vm), gui::p2pS(1.3f, vm), std::to_string(this->player->getAttributeComponent()->level), gui::p2pS(1.3f, vm));
}

void PlayerGui::initBars()
{
												//Front width, bckwdth, height, xpos, ypos, backcolor, fillcolor, player, font, vm (optional)fontsize
	this->HPBar = std::make_unique<progressBar>(gui::p2pX(13.f, vm), gui::p2pX(13.f, vm), gui::p2pY(3.35f, vm), gui::p2pX(2.6f, vm), gui::p2pY(1.1f, vm), sf::Color(50, 50, 50, 200), sf::Color(250,20,20,210), this->player, this->font, vm, gui::p2pX(1.f, vm));
	this->ExpBar = std::make_unique<progressBar>(gui::p2pX(13.85f, vm), gui::p2pX(14.85f, vm), gui::p2pY(1.f, vm), gui::p2pX(.7f, vm), gui::p2pY(8.4f, vm), sf::Color(50, 50, 50, 200), sf::Color(140, 140, 140, 250), this->player, this->font, vm, 0, gui::p2pS(.4f, vm));
	this->EnergyBar = std::make_unique<progressBar>(gui::p2pX(13.f, vm), gui::p2pX(13.f, vm), gui::p2pY(3.35f, vm), gui::p2pX(2.6f, vm), gui::p2pY(4.8f, vm), sf::Color(50, 50, 50, 200), sf::Color(20, 20, 250, 210), this->player, this->font, vm, gui::p2pX(1.f, vm));
}

PlayerGui::PlayerGui(std::shared_ptr<Player> player, sf::Font& font, sf::VideoMode& vm)
	: player(player), font(font), vm(vm)
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
	if (this->player->getAttributeComponent()->energyUpdate) {
		EnergyBarText = "Energy: " + std::to_string(this->player->getAttributeComponent()->energy) + " / " + std::to_string(this->player->getAttributeComponent()->energyMax);
		tempPercent = (float)player->getAttributeComponent()->energy / (float)player->getAttributeComponent()->energyMax;
		EnergyBar->update(dt, tempPercent, EnergyBarText);
		this->player->getAttributeComponent()->energyUpdate = false;
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
	EnergyBar->render(target);
	for (auto& i : this->buttons)
	{
		i.second->render(target);
	}
}


