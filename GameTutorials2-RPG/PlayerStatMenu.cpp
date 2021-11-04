#include "stdafx.h"
#include "PLayerStatMenu.h"

PLayerStatMenu::PLayerStatMenu(sf::RenderWindow& window, sf::Font& font)
	: font(font)
{
	//Init background
	background.setSize(
		sf::Vector2f(
			static_cast<float>(window.getSize().x),
			static_cast<float>(window.getSize().y)
		));
	background.setFillColor(sf::Color(20, 20, 20, 100));

	//Init container
	container.setSize(
		sf::Vector2f(
			static_cast<float>(window.getSize().x) / 4.f,
			static_cast<float>(window.getSize().y) - 90.f)
	);
	container.setFillColor(sf::Color(50, 50, 50, 200));
	container.setPosition(
		static_cast<float>((window.getView().getCenter().x - container.getSize().x / 2)), //centers it on x
		30.f
	);

	//Init text
	menuText.setFont(font);
	menuText.setFillColor(sf::Color(255, 255, 255, 200));
	menuText.setCharacterSize(80);
	menuText.setString("PAUSE MENU");
	menuText.setPosition(
		window.getView().getCenter().x - menuText.getGlobalBounds().width / 2,
		container.getPosition().y + 20
	);
}

PLayerStatMenu::~PLayerStatMenu()
{
}

std::map<std::string, std::unique_ptr<gui::Button>>& PLayerStatMenu::getButtons()
{
	return buttons;
}

const bool PLayerStatMenu::isButtonPressed(const std::string key)
{
	return buttons[key]->isPressed();
}

void PLayerStatMenu::addButton(const std::string key, float y, const std::string text)
{
	float width = 250.f;
	float height = 75.f;
	float x = container.getPosition().x + container.getSize().x / 2 - width / 2.f;
	buttons[key] = std::make_unique<gui::Button>(x, y, width, height,
		font, text, 50,
		sf::Color(245, 212, 0, 250), sf::Color(255, 222, 0, 255), sf::Color(0, 0, 250, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0)
		);

}

void PLayerStatMenu::update(const float& dt, const sf::Vector2f& mousePos)
{
	for (auto& i : buttons)
	{
		i.second->update(dt, mousePos);
	}
}

void PLayerStatMenu::render(sf::RenderTarget& target)
{
	target.draw(background);
	target.draw(container);

	for (auto& i : buttons)
	{
		i.second->render(target);
	}

	target.draw(menuText);
}
