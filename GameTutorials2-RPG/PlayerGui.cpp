#include "stdafx.h"
#include "Player.h"
#include "PlayerGui.h"
#include "Attribute.h"
#include "Skills.h"

void PlayerGui::initLevel()
{
	addButton("LEVEL", gui::p2pX(2.6f, vm), gui::p2pY(4.6f, vm), gui::p2pS(1.3f, vm), std::to_string(player->getComponent<Attribute>()->level), (short)gui::p2pS(1.3f, vm));
}

void PlayerGui::initBars()
{			
	
	//Front width, bckwdth, height, xpos, ypos, backcolor, fillcolor, player, font, vm (optional)fontsize
	addBar("HPBar", gui::p2pX(13.f, vm), gui::p2pX(13.f, vm), gui::p2pY(3.35f, vm), gui::p2pX(2.6f, vm), gui::p2pY(1.1f, vm), sf::Color(50, 50, 50, 200), sf::Color(250, 20, 20, 210), player, font, vm, static_cast<int>(gui::p2pX(1.f, vm)));
	addBar("ExpBar", gui::p2pX(13.85f, vm), gui::p2pX(14.85f, vm), gui::p2pY(1.f, vm), gui::p2pX(.7f, vm), gui::p2pY(8.4f, vm), sf::Color(50, 50, 50, 200), sf::Color(140, 140, 140, 250), player, font, vm, 0, static_cast<int>(gui::p2pS(.4f, vm)));
	addBar("EnergyBar", gui::p2pX(13.f, vm), gui::p2pX(13.f, vm), gui::p2pY(3.35f, vm), gui::p2pX(2.6f, vm), gui::p2pY(4.8f, vm), sf::Color(50, 50, 50, 200), sf::Color(20, 20, 250, 210), player, font, vm, static_cast<int>(gui::p2pX(1.f, vm)));
	
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

void PlayerGui::addBar
(
	std::string key,
	float frontWidth, float backWidth, float height, float xPos, float yPos,
	sf::Color backgroundColor, sf::Color fillColor, std::shared_ptr<Player>& player,
	sf::Font& font, sf::VideoMode& vm, int offset, int fontSize
)
{
	bars[key] = std::make_unique<gui::progressBar>(frontWidth, backWidth, height, xPos, yPos, backgroundColor, fillColor, player, font, vm, offset, fontSize);
}



void PlayerGui::updateBars(const float& dt)
{

	if (player->getComponent<Attribute>()->healthUpdate) {
		ProgressBarText = "HP: " + std::to_string(player->getComponent<Attribute>()->hp) + " / " + std::to_string(player->getComponent<Attribute>()->hpMax);
		tempPercent = (float)player->getComponent<Attribute>()->hp / static_cast<float>(player->getComponent<Attribute>()->hpMax);
		bars.at("HPBar")->update(dt, tempPercent, ProgressBarText);
	player->getComponent<Attribute>()->healthUpdate = false;
	}
	if (player->getComponent<Attribute>()->expUpdate) {
		ProgressBarText = "EXP: " + std::to_string(player->getComponent<Attribute>()->exp) + " / " + std::to_string(player->getComponent<Attribute>()->expnext);
		tempPercent = (float)player->getComponent<Attribute>()->exp / static_cast<float>(player->getComponent<Attribute>()->expnext);
		bars.at("ExpBar")->update(dt, tempPercent, ProgressBarText);
		player->getComponent<Attribute>()->expUpdate = false;
	}
	if (player->getComponent<Attribute>()->energyUpdate) {
		ProgressBarText = "Energy: " + std::to_string(player->getComponent<Attribute>()->energy) + " / " + std::to_string(player->getComponent<Attribute>()->energyMax);
		tempPercent = (float)player->getComponent<Attribute>()->energy / static_cast<float>(player->getComponent<Attribute>()->energyMax);
		bars.at("EnergyBar")->update(dt, tempPercent, ProgressBarText);
		player->getComponent<Attribute>()->energyUpdate = false;
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
				if (player->getComponent<Attribute>()->levelUpdate) {
					i.second->setText(std::to_string(player->getComponent<Attribute>()->level));
					player->getComponent<Attribute>()->levelUpdate = false;
				}
			}
		}
}

void PlayerGui::render(sf::RenderTarget& target)
{
	//Render Bars
	for (auto& iter : bars) {
		iter.second->render(target);
	}
	//Render Buttons
	for (auto& i : buttons)
	{
		i.second->render(target);
	}
}


