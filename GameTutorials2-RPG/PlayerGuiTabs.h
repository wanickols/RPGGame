#pragma once

class Entity;
class Tab;


enum PLAYER_TABS { CHARACTER_TAB = 0, INVENTORY_TAB };

class PlayerGuiTabs
{


public:
	PlayerGuiTabs(sf::VideoMode& vm, sf::Font& font, std::shared_ptr<Entity> player);
	virtual ~PlayerGuiTabs();

	const bool getKeyTime();
	const bool tabsOpen();

	void toggleTab(const int tab_index);

	void update();
	void render(sf::RenderTarget& target);
private:

	std::vector<std::unique_ptr<Tab>> tabs;

	//Core
	sf::VideoMode& vm;
	sf::Font& font;
	std::shared_ptr<Entity> player;
	gui::KeyTimeManger keyTimeManager;
	
	//Tabs

	//Character Tab

	//Private functions
	void initTabs();
	void initKeyTime();
};



