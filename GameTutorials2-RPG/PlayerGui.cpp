#include "stdafx.h"
#include "Player.h"
#include "PlayerGui.h"

progressBar::progressBar(float frontWidth, float backWidth, float height, float xPos, float yPos, sf::Color backgroundColor, sf::Color fillColor, std::shared_ptr<Player>& player, sf::Font& font, sf::VideoMode& vm, int offset, int fontSize)
	: fullWidth(frontWidth), percentWidth(100), height(height), player(player)
{
	text.setFont(font);
	text.setCharacterSize(fontSize);
	text.setFillColor(sf::Color(250,250,250,230));
	text.setPosition(xPos + (float)fontSize/2 + (float)offset*2, yPos + (height/2) - ((float)fontSize/2));
	text.setString("HP:" + 100);
	
	ProgBarBack.setSize(sf::Vector2f(backWidth, height));
	ProgBarBack.setFillColor(backgroundColor);
	ProgBarBack.setPosition(xPos, yPos);
	ProgBarBack.setOutlineColor(sf::Color(255,255,255,250));
	ProgBarBack.setOutlineThickness(gui::p2pS(0.1f, vm));

	ProgBarIn.setSize(sf::Vector2f(frontWidth, height));
	ProgBarIn.setFillColor(fillColor);
	ProgBarIn.setPosition(xPos, yPos);
}

void progressBar::update(const float& dt, float& percentWidth)
{
	ProgBarIn.setSize(sf::Vector2f((float)std::floor(percentWidth * fullWidth), height));
	ProgBarIn.setSize(sf::Vector2f((float)std::floor(percentWidth * fullWidth), height));
}

void progressBar::update(const float& dt, float& percentWidth, std::string textString)
{

	update(dt, percentWidth);
	text.setString(textString);
}

void progressBar::render(sf::RenderTarget& target)
{
	target.draw(ProgBarBack);
	target.draw(ProgBarIn);
	target.draw(text);
}

void PlayerGui::initLevel()
{
	addButton("LEVEL", gui::p2pX(2.6f, vm), gui::p2pY(4.6f, vm), gui::p2pS(1.3f, vm), std::to_string(player->getAttributeComponent()->level), (short)gui::p2pS(1.3f, vm));
}

void PlayerGui::initBars()
{

												//Front width, bckwdth, height, xpos, ypos, backcolor, fillcolor, player, font, vm (optional)fontsize
	HPBar = std::make_unique<progressBar>(gui::p2pX(13.f, vm), gui::p2pX(13.f, vm), gui::p2pY(3.35f, vm), gui::p2pX(2.6f, vm), gui::p2pY(1.1f, vm), sf::Color(50, 50, 50, 200), sf::Color(250,20,20,210), player, font, vm, static_cast<int>(gui::p2pX(1.f, vm)));
	ExpBar = std::make_unique<progressBar>(gui::p2pX(13.85f, vm), gui::p2pX(14.85f, vm), gui::p2pY(1.f, vm), gui::p2pX(.7f, vm), gui::p2pY(8.4f, vm), sf::Color(50, 50, 50, 200), sf::Color(140, 140, 140, 250), player, font, vm, 0, static_cast<int>(gui::p2pS(.4f, vm)));
	EnergyBar = std::make_unique<progressBar>(gui::p2pX(13.f, vm), gui::p2pX(13.f, vm), gui::p2pY(3.35f, vm), gui::p2pX(2.6f, vm), gui::p2pY(4.8f, vm), sf::Color(50, 50, 50, 200), sf::Color(20, 20, 250, 210), player, font, vm, static_cast<int>(gui::p2pX(1.f, vm)));
}

PlayerGui::PlayerGui(std::shared_ptr<Player> player, sf::Font& font, sf::VideoMode& vm)
	: player(player), font(font), vm(vm)
{
	initLevel();
	initBars();
}

void PlayerGui::addButton(const std::string& key, const float& x, const float& y, const float& width, const float& height, const std::string& text, const short& textSize)
{
	buttons[key] = std::make_unique<gui::Button>(x, y, width, height,
		font, text, textSize,
		sf::Color(245, 212, 0, 250), sf::Color(255, 222, 0, 255), sf::Color(0, 0, 250, 50),
		sf::Color(70, 70, 70, 255), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 255), gui::button_types::RECTANGLE
		);
}

void PlayerGui::addButton(const std::string& key, const float& x, const float& y, const float& radius, const std::string& text, const short& textSize)
{
	buttons[key] = std::make_unique<gui::Button>(x, y, radius, radius,
		font, text, textSize,
		sf::Color(255, 255, 255, 245), sf::Color(255, 255, 255, 255), sf::Color(250, 250, 250, 250),
		sf::Color(120, 120, 120, 255), sf::Color(150, 150, 150, 255), sf::Color(100, 100, 100, 255), gui::button_types::CIRCLE, 3.f
		, sf::Color(255, 255, 255, 250), sf::Color(230,230,230,235)
		);
}

void PlayerGui::updateBars(const float& dt)
{

	if (player->getAttributeComponent()->healthUpdate) {
		HPBarText = "HP: " + std::to_string(player->getAttributeComponent()->hp) + " / " + std::to_string(player->getAttributeComponent()->hpMax);
		tempPercent = (float)player->getAttributeComponent()->hp / static_cast<float>(player->getAttributeComponent()->hpMax);
		HPBar->update(dt, tempPercent, HPBarText);
	player->getAttributeComponent()->healthUpdate = false;
	}
	if (player->getAttributeComponent()->expUpdate) {
		ExpBarText = "EXP: " + std::to_string(player->getAttributeComponent()->exp) + " / " + std::to_string(player->getAttributeComponent()->expnext);
		tempPercent = (float)player->getAttributeComponent()->exp / static_cast<float>(player->getAttributeComponent()->expnext);
		ExpBar->update(dt, tempPercent, ExpBarText);
		player->getAttributeComponent()->expUpdate = false;
	}
	if (player->getAttributeComponent()->energyUpdate) {
		EnergyBarText = "Energy: " + std::to_string(player->getAttributeComponent()->energy) + " / " + std::to_string(player->getAttributeComponent()->energyMax);
		tempPercent = (float)player->getAttributeComponent()->energy / static_cast<float>(player->getAttributeComponent()->energyMax);
		EnergyBar->update(dt, tempPercent, EnergyBarText);
		player->getAttributeComponent()->energyUpdate = false;
	}
}

//Functions
void PlayerGui::update(const float& dt, const sf::Vector2f& mousePos)
{

	updateBars(dt);
		
	
		for (auto& i : buttons)
		{
			i.second->update(mousePos);
			if (i.first == "LEVEL") {
				if (player->getAttributeComponent()->levelUpdate) {
					i.second->setText(std::to_string(player->getAttributeComponent()->level));
					player->getAttributeComponent()->levelUpdate = false;
				}
			}
		}
}

void PlayerGui::render(sf::RenderTarget& target)
{
	HPBar->render(target);
	ExpBar->render(target);
	EnergyBar->render(target);
	for (auto& i : buttons)
	{
		i.second->render(target);
	}
}


