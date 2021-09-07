#include "stdafx.h"
#include "GraphicsSettings.h"


GraphicsSettings::GraphicsSettings()
{

	resolution = sf::VideoMode::getDesktopMode();
	fullscreen = false;
	currMode = 0;
	verticalSync = false;
	frameRateLimit = 120;
	contextSettings.antialiasingLevel = 0;
	videModes = sf::VideoMode::getFullscreenModes();
}

//Functions
void GraphicsSettings::saveToFile(const std::string path)
{
	std::ofstream ofs(path);

	//vairables for file

	//pulls info from a file for window initialization
	if (ofs.is_open()) {

		ofs << title << '\n';
		ofs << resolution.width << " " << resolution.height << '\n';
		ofs << currMode << '\n';
		ofs << fullscreen << '\n';
		ofs << frameRateLimit << '\n';
		ofs << verticalSync << '\n';
		ofs << contextSettings.antialiasingLevel << '\n';
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

		std::getline(ifs, title);
		ifs >> resolution.width >> resolution.height;
		ifs >> currMode;
		ifs >> fullscreen;
		ifs >> frameRateLimit;
		ifs >> verticalSync;
		ifs >> contextSettings.antialiasingLevel;
	}

	ifs.close();

	//initializes the window

}