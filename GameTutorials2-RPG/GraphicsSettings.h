#pragma once
class GraphicsSettings {
public:
	GraphicsSettings();
	
	//variables
	std::string title;
	sf::VideoMode resolution;
	unsigned int currMode;
	bool fullscreen;
	bool verticalSync;
	unsigned short frameRateLimit;
	sf::ContextSettings contextSettings;
	std::vector<sf::VideoMode> videModes;

	//Functions
	void saveToFile(const std::string path);
	void loadFromFile(const std::string path);

};

