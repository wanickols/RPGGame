#include "stdafx.h"
#include "GraphicsSettings.h"


GraphicsSettings::GraphicsSettings()
{

	this->resolution = sf::VideoMode::getDesktopMode();
	this->fullscreen = false;
	currMode = 0;
	this->verticalSync = false;
	this->frameRateLimit = 120;
	this->contextSettings.antialiasingLevel = 0;
	this->videModes = sf::VideoMode::getFullscreenModes();
}

//Functions
void GraphicsSettings::saveToFile(const std::string path)
{
	std::ofstream ofs(path);

	//vairables for file

	//pulls info from a file for window initialization
	if (ofs.is_open()) {

		ofs << this->title << '\n';
		ofs << this->resolution.width << " " << this->resolution.height << '\n';
		ofs << this->currMode << '\n';
		ofs << this->fullscreen << '\n';
		ofs << this->frameRateLimit << '\n';
		ofs << this->verticalSync << '\n';
		ofs << this->contextSettings.antialiasingLevel << '\n';
	}

	ofs.close();
}

void GraphicsSettings::loadFromFile(const std::string path)
{
	//creates SFML window from window.init option? :D

	std::ifstream ifs(path);

	//vairables for file

	//pulls info from a file for window initialization
	if (ifs.is_open()) {

		std::getline(ifs, this->title);
		ifs >> this->resolution.width >> this->resolution.height;
		ifs >> this->currMode;
		ifs >> this->fullscreen;
		ifs >> this->frameRateLimit;
		ifs >> this->verticalSync;
		ifs >> this->contextSettings.antialiasingLevel;
	}

	ifs.close();

	//initializes the window

}