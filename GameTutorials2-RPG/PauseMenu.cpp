#include "stdafx.h"
#include "PauseMenu.h"

PauseMenu::PauseMenu(sf::RenderWindow& window, sf::Font& font, float button_width, float button_height, int character_size)
	: font(font), buttonWidth(button_width), buttonHeight(button_height), characterSize(character_size)
{
	//Init background
	background.setSize(
		sf::Vector2f(
			static_cast<float>(window.getSize().x),
			static_cast<float>(window.getSize().y)
		));
	background.setFillColor(sf::Color(20, 20, 20, 100));

	//Init container
	container.setSize(sf::Vector2f(buttonWidth*1.92f, buttonHeight*13.6f));
	container.setFillColor(sf::Color(50, 50, 50, 200));
	container.setPosition(
		static_cast<float>((window.getView().getCenter().x - container.getSize().x / 2)), //centers it on x
		30.f
	);

	//Init text
	menuText.setFont(font);
	menuText.setFillColor(sf::Color(255, 255, 255, 200));
	menuText.setCharacterSize((int)(characterSize * 1.2f));
	menuText.setString("PAUSE MENU");
	menuText.setPosition(
		window.getView().getCenter().x - menuText.getGlobalBounds().width / 2,
		container.getPosition().y + 20
	);
}

PauseMenu::~PauseMenu()
{
}

std::map<std::string, std::unique_ptr<gui::Button>>& PauseMenu::getButtons()
{
	return buttons;
}

const bool PauseMenu::isButtonPressed(const std::string key)
{
	return buttons[key]->isPressed();
}

void PauseMenu::addButton(const std::string key, float y, const std::string text)
{
	float x = container.getPosition().x + container.getSize().x / 2 - buttonWidth / 2.f;
	buttons[key] = std::make_unique<gui::Button>(x, y, buttonWidth, buttonHeight,
		font, text, characterSize,
		sf::Color(245, 212, 0, 250), sf::Color(255, 222, 0, 255), sf::Color(0, 0, 250, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0)
		);

}

void PauseMenu::update(const float& dt, const sf::Vector2f& mousePos)
{
	for (auto& i : buttons)
	{
		i.second->update(dt, mousePos);
	}
}

void PauseMenu::render(sf::RenderTarget& target)
{
	target.draw(background);
	target.draw(container);

	for (auto& i : buttons)
	{
		i.second->render(target);
	}

	target.draw(menuText);
}
