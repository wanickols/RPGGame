#include "stdafx.h"
#include "TextTagSystem.h"

//Private functions
void TextTagSystem::initVariables()
{

}

void TextTagSystem::initFonts(std::string font_file)
{
	//
	if (!this->font.loadFromFile(font_file))
		std::cout << "ERROR::TEXTTAGSYSTEM::CONSTRUCTOR::Failed to load font " << font_file << "\n";
}

void TextTagSystem::initTagTemplates()
{
	this->tagTemplates[DEFAULT_TAG] = std::make_shared<TextTagSystem::TextTag>(this->font, "1", 100.f, 100.f, 0.f, -1.f, sf::Color::White, 25, 100.f, true, 200.f, 200.f, 2);
	this->tagTemplates[NEGATIVE_TAG] = std::make_shared<TextTagSystem::TextTag>(this->font, "2", 100.f, 100.f, 0.f, 1.f, sf::Color::Red, 25, 100.f, true, 200.f, 200.f, 1);
	this->tagTemplates[EXPERIENCE_TAG] = std::make_shared<TextTagSystem::TextTag>(this->font, "3", 100.f, 100.f, 0.f, -1.f, sf::Color::Cyan, 30, 200.f, true, 200.f, 200.f, 2);
}

//Constructor / Destructor
TextTagSystem::TextTagSystem(std::string font_file)
{
	initFonts(font_file);
	this->initVariables();
	this->initTagTemplates();
}

TextTagSystem::~TextTagSystem()
{}

//Functions
void TextTagSystem::addTextTag(const unsigned tag_type, const float pos_x, const float pos_y, const std::string str, const std::string prefix = "", const std::string postfix = "")
{
	std::stringstream ss;
	ss << prefix << " " << str << " " << postfix;
	this->tags.push_back(std::make_shared<TextTag>(this->tagTemplates[tag_type], pos_x, pos_y, ss.str()));
}

void TextTagSystem::addTextTag(const unsigned tag_type, const float pos_x, const float pos_y, const int i, const std::string prefix = "", const std::string postfix = "")
{
	std::stringstream ss;
	ss << prefix << " " << i << " " << postfix;
	this->tags.push_back(std::make_shared<TextTag>(this->tagTemplates[tag_type], pos_x, pos_y, ss.str()));
}

void TextTagSystem::addTextTag(const unsigned tag_type, const float pos_x, const float pos_y, const float f, const std::string prefix = "", const std::string postfix = "")
{
	std::stringstream ss;
	ss << prefix << " " << f << " " << postfix;
	this->tags.push_back(std::make_shared<TextTagSystem::TextTag>(this->tagTemplates[tag_type], pos_x, pos_y, ss.str()));
}

void TextTagSystem::update(const float& dt)
{
	auto i = tags.begin();
	while (i != tags.end())
	{
		i->get()->update(dt);
		if (i->get()->isExpired())
		{
			std::cout << "text tag deleted \n";
			i = tags.erase(i);
		}
		else
		{
			++i;
		}
	}
}

void TextTagSystem::render(sf::RenderTarget& target)
{
	for (auto& tag : this->tags)
	{
		tag->render(target);
	}
}


