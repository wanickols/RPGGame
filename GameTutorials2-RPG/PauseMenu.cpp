#include "stdafx.h"
#include "PauseMenu.h"

PauseMenu::PauseMenu(sf::RenderWindow& window, sf::Font& font, float button_width, float button_height, int character_size)
	: font(font), buttonWidth(button_width), buttonHeight(button_height), characterSize(character_size)
{
	//Init background
	this->background.setSize(
		sf::Vector2f(
			static_cast<float>(window.getSize().x),
			static_cast<float>(window.getSize().y)
		));
	this->background.setFillColor(sf::Color(20, 20, 20, 100));

	//Init container
	this->container.setSize(sf::Vector2f(buttonWidth*1.92f, buttonHeight*13.6f));
	this->container.setFillColor(sf::Color(50, 50, 50, 200));
	this->container.setPosition(
		static_cast<float>((window.getView().getCenter().x - this->container.getSize().x / 2)), //centers it on x
		30.f
	);

	//Init text
	this->menuText.setFont(font);
	this->menuText.setFillColor(sf::Color(255, 255, 255, 200));
	this->menuText.setCharacterSize((int)(characterSize * 1.2f));
	this->menuText.setString("PAUSE MENU");
	this->menuText.setPosition(
		window.getView().getCenter().x - this->menuText.getGlobalBounds().width / 2,
		this->container.getPosition().y + 20
	);
}

PauseMenu::~PauseMenu()
{
}

std::map<std::string, std::unique_ptr<gui::Button>>& PauseMenu::getButtons()
{
	return this->buttons;
}

const bool PauseMenu::isButtonPressed(const std::string key)
{
	return this->buttons[key]->isPressed();
}

void PauseMenu::addButton(const std::string key, float y, const std::string text)
{
	float x = this->container.getPosition().x + this->container.getSize().x / 2 - buttonWidth / 2.f;
	this->buttons[key] = std::make_unique<gui::Button>(x, y, buttonWidth, buttonHeight,
		this->font, text, characterSize,
		sf::Color(245, 212, 0, 250), sf::Color(255, 222, 0, 255), sf::Color(0, 0, 250, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0)
		);

}

void PauseMenu::update(const sf::Vector2f& mousePos)
{
	for (auto& i : this->buttons)
	{
		i.second->update(mousePos);
	}
}

void PauseMenu::render(sf::RenderTarget& target)
{
	target.draw(this->background);
	target.draw(this->container);

	for (auto& i : this->buttons)
	{
		i.second->render(target);
	}

	target.draw(this->menuText);
}
