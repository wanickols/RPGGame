#include "stdafx.h"
#include "State.h"
#include "GraphicsSettings.h"
#include "StateData.h"




//Initializations
void State::initFont()
{
	if (!font.loadFromFile("Fonts/Dosis-Light.ttf")) {

		throw("ERROR::STATE::COULD NOT LOAD FONT");
	}
}

//Constructors
State::State(std::shared_ptr<StateData> state_data)
{
	initFont();
	stateData = state_data;
	window = state_data->window;
	states = state_data->states;
	GraphicsSettings = state_data->GraphicsSettings;
	supportedKeys = state_data->supportedKeys;
	quit = false;
	paused = false;
	keyTime = 0.f;
	keyTimeMax = 15.f;
	gridSize = state_data->gridSize;
	mapSize = state_data->mapSize;
	characterSize = static_cast<int>(gui::p2pX(2.6f, GraphicsSettings->resolution));
}

State::~State()
{}

//State stuffers
void State::endState()
{
	quit = true;
}

void State::pauseState()
{
	paused = true;
}

void State::unpauseState()
{
	paused = false;
}

//Accessors
const bool& State::getQuit() const
{
	return quit;
}

const bool State::getKeyTime()
{
	if (keyTime > keyTimeMax)
	{
		keyTime = 0.f;
		return true;
	}
	return false;
}

//Functions
void State::updateMousePositions(std::unique_ptr<sf::View> view)
{
	mousePosScreen = sf::Mouse::getPosition();
	mousePosWindow = sf::Mouse::getPosition(*window);
	
	if(view)
		window->setView(*view);

	mousePosView = window->mapPixelToCoords(sf::Mouse::getPosition(*window));
	mousePosGrid = 
		sf::Vector2i(
		static_cast<int>(mousePosView.x) / static_cast<int>(gridSize),
			static_cast<int>(mousePosView.y) / static_cast<int>(gridSize)
		);

	window->setView(window->getDefaultView());
}

void State::updateKeyTime(const float& dt)
{
	if (keyTime < keyTimeMax) {
		keyTime += 100.f * dt;
	}
}

std::unique_ptr<gui::Button> State::addButton(float x, float y, const std::string text, float width, float height, short characterSize)
{
	//Takes pixel values from addbutton in 1920/1080 and converts them to percentages so they stay that way on every screen size. 
	width = gui::p2pX(width / 19.20f, GraphicsSettings->resolution);
	height = gui::p2pY(height / 10.80f, GraphicsSettings->resolution);
	characterSize = static_cast<short>(gui::p2pX(static_cast<float>(characterSize) / 19.20f, GraphicsSettings->resolution));

	return std::make_unique<gui::Button>(x, y, width, height,
		font, text, characterSize,
		sf::Color(245, 212, 0, 250), sf::Color(255, 222, 0, 255), sf::Color(0, 0, 250, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0)
		);
}

std::unique_ptr<gui::Button> State::addButton(float x, float y, const std::string text, float width, float height, short characterSize,
	sf::Color text_idle_color, sf::Color text_hover_color, sf::Color text_active_color, gui::button_types type,
	sf::Color idle_color, sf::Color hover_color, sf::Color active_color)
{
	return std::make_unique<gui::Button>(x, y, width, height,
		font, text, characterSize,
		text_idle_color, text_hover_color, text_active_color,
		idle_color, hover_color, active_color, type
		);
}



