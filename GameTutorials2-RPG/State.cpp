#include "stdafx.h"
#include "State.h"
#include "GraphicsSettings.h"
#include "StateData.h"


//Initializations
void State::initFont()
{
	if (!this->font.loadFromFile("Fonts/Dosis-Light.ttf")) {

		throw("ERROR::STATE::COULD NOT LOAD FONT");
	}
}

//Constructors
State::State(std::shared_ptr<StateData> state_data)
{
	initFont();
	this->stateData = state_data;
	this->window = state_data->window;
	this->states = state_data->states;
	this->gfxSettings = state_data->GraphicsSettings;
	this->supportedKeys = state_data->supportedKeys;
	this->quit = false;
	this->paused = false;
	keyTime = 0.f;
	keyTimeMax = 15.f;
	this->gridSize = state_data->gridSize;
	this->mapSize = state_data->mapSize;
}

State::~State()
{}

//State stuffers
void State::endState()
{
	this->quit = true;
}

void State::pauseState()
{
	this->paused = true;
}

void State::unpauseState()
{
	this->paused = false;
}

//Accessors
const bool& State::getQuit() const
{
	return this->quit;
}

const bool State::getKeyTime()
{
	if (this->keyTime > this->keyTimeMax)
	{
		this->keyTime = 0.f;
		return true;
	}
	return false;
}

//Functions
void State::updateMousePositions(std::unique_ptr<sf::View> view)
{
	this->mousePosScreen = sf::Mouse::getPosition();
	this->mousePosWindow = sf::Mouse::getPosition(*this->window);
	
	if(view)
		this->window->setView(*view);

	this->mousePosView = this->window->mapPixelToCoords(sf::Mouse::getPosition(*this->window));
	this->mousePosGrid = 
		sf::Vector2i(
		static_cast<int>(this->mousePosView.x) / static_cast<int>(this->gridSize),
			static_cast<int>(this->mousePosView.y) / static_cast<int>(this->gridSize)
		);

	this->window->setView(this->window->getDefaultView());
}

void State::updateKeyTime(const float& dt)
{
	if (keyTime < keyTimeMax) {
		keyTime += 100.f * dt;
	}
}

std::unique_ptr<gui::Button> State::addButton(float x, float y, const std::string text, float width, float height, int characterSize)
{
	return std::make_unique<gui::Button>(x, y, width, height,
		this->font, text, characterSize,
		sf::Color(245, 212, 0, 250), sf::Color(255, 222, 0, 255), sf::Color(0, 0, 250, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0)
		);
}

std::unique_ptr<gui::Button> State::addButton(float x, float y, const std::string text, float width, float height, int characterSize,
	sf::Color text_idle_color, sf::Color text_hover_color, sf::Color text_active_color,
	sf::Color idle_color, sf::Color hover_color, sf::Color active_color)
{
	return std::make_unique<gui::Button>(x, y, width, height,
		this->font, text, characterSize,
		text_idle_color, text_hover_color, text_active_color,
		idle_color, hover_color, active_color
		);
}



