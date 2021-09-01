#include "stdafx.h"
#include "PLayerStatMenu.h"

PLayerStatMenu::PLayerStatMenu(sf::RenderWindow& window, sf::Font& font)
	: font(font)
{
	//Init background
	this->background.setSize(
		sf::Vector2f(
			static_cast<float>(window.getSize().x),
			static_cast<float>(window.getSize().y)
		));
	this->background.setFillColor(sf::Color(20, 20, 20, 100));

	//Init container
	this->container.setSize(
		sf::Vector2f(
			static_cast<float>(window.getSize().x) / 4.f,
			static_cast<float>(window.getSize().y) - 90.f)
	);
	this->container.setFillColor(sf::Color(50, 50, 50, 200));
	this->container.setPosition(
		static_cast<float>((window.getView().getCenter().x - this->container.getSize().x / 2)), //centers it on x
		30.f
	);

	//Init text
	this->menuText.setFont(font);
	this->menuText.setFillColor(sf::Color(255, 255, 255, 200));
	this->menuText.setCharacterSize(80);
	this->menuText.setString("PAUSE MENU");
	this->menuText.setPosition(
		window.getView().getCenter().x - this->menuText.getGlobalBounds().width / 2,
		this->container.getPosition().y + 20
	);
}

PLayerStatMenu::~PLayerStatMenu()
{
}

std::map<std::string, std::unique_ptr<gui::Button>>& PLayerStatMenu::getButtons()
{
	return this->buttons;
}

const bool PLayerStatMenu::isButtonPressed(const std::string key)
{
	return this->buttons[key]->isPressed();
}

void PLayerStatMenu::addButton(const std::string key, float y, const std::string text)
{
	float width = 250.f;
	float height = 75.f;
	float x = this->container.getPosition().x + this->container.getSize().x / 2 - width / 2.f;
	this->buttons[key] = std::make_unique<gui::Button>(x, y, width, height,
		this->font, text, 50,
		sf::Color(245, 212, 0, 250), sf::Color(255, 222, 0, 255), sf::Color(0, 0, 250, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0)
		);

}

void PLayerStatMenu::update(const sf::Vector2f& mousePos)
{
	for (auto& i : this->buttons)
	{
		i.second->update(mousePos);
	}
}

void PLayerStatMenu::render(sf::RenderTarget& target)
{
	target.draw(this->background);
	target.draw(this->container);

	for (auto& i : this->buttons)
	{
		i.second->render(target);
	}

	target.draw(this->menuText);
}
