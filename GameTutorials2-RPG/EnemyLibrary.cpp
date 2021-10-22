#include "stdafx.h"
#include "EnemyLibrary.h"
#include "Enemy.h"
#include "Attribute.h"
#include "EnemyData.h"
#include "ComponentInclude.h"
#include "Presets.h"

//Take in a File
EnemyLibrary::EnemyLibrary()
{

	
	//Init Textures
	if (textureDoc.LoadFile("test.xml") != tinyxml2::XML_SUCCESS)
	{
		std::cout << "ERROR::ENGINE::LEVEL XML FILE COULD NOT LOAD \n" << "test.xml";
		exit(1);
	}
	tinyxml2::XMLElement* root = textureDoc.FirstChildElement("Map"); //root of xml
	tinyxml2::XMLElement* enemy_1 = root->FirstChildElement("Enemy"); //First object
	tinyxml2::XMLElement* spritesheet;

	int i = 0;
	while (enemy_1) { //loops until no more objects exist
		textures[enemy_1->Attribute("name")] = std::make_shared<sf::Texture>(); //makes texture
		spritesheet = enemy_1->FirstChildElement("SpriteSheet");
		types[enemy_1->IntAttribute("typeNum")] = enemy_1->Attribute("name");
		if (!textures.at(enemy_1->Attribute("name"))->loadFromFile(spritesheet->Attribute("path")))
		{
			std::cout << "ERROR::EnemyLibrary::FAILED TO LOAD TEXTURE " << spritesheet->Attribute("path") << '\n';
		}
		enemy_1 = enemy_1->NextSiblingElement();
	}

	
	

	//textures["Bird"] = std::make_shared<sf::Texture>();
	//if (!textures.at("Bird")->loadFromFile("Resources/Images/Sprites/Enemies/bird1.png"))
		//std::cout << "ERROR::EnemyLibrary::FAILED TO LOAD BIRD " << '\n';

	initComponents();
}

std::shared_ptr<sf::Texture> EnemyLibrary::find(std::string name)
{
	return textures.find(name)->second;
}

void EnemyLibrary::update(const float& dt, bool playerAttack, std::shared_ptr<Entity> attacker)
{


	if (!enemies.empty()) {
		auto i = enemies.begin();
		while (i != enemies.end())
		{
			if (playerAttack)
				if (i->get()->getDistance(*attacker) < attacker->getComponent<Attribute>()->range)
				{
					i->get()->getComponent<Attribute>()->loseHealth(10);
					std::cout << i->get()->getComponent<EnemyData>()->getName() << " Hit! \n";
				}
			i->get()->update(dt);

			if (i->get()->getComponent<Attribute>()->isDead()) {
				i = enemies.erase(i);	
			}
			else
			{
				++i;
			}
		}
	}
}

void EnemyLibrary::render(sf::RenderTarget& target, sf::Shader* shader, sf::Vector2f light_position, const bool show_hitbox)
{
	for (auto& i : enemies)
	{
		i->render(target, shader, light_position, true);
	}
}

std::string EnemyLibrary::translateType(int type)
{
	//uese type map to return type
	//Rat = 0
	return types.find(type)->second;
}

bool EnemyLibrary::createComponents(Enemy& enemy, std::string name, int x, int y)
{
	//0
	if (componentPresets.find(name)->second->hitBox.created)
	{
		std::shared_ptr<Hitbox> hitBox = std::make_shared<Hitbox>(enemy.getSprite(), componentPresets.find(name)->second->hitBox.offSetX, componentPresets.find(name)->second->hitBox.offSetY, componentPresets.find(name)->second->hitBox.width, componentPresets.find(name)->second->hitBox.height, &enemy);
		enemy.addComponent(hitBox);
	}
	//1
	if (componentPresets.find(name)->second->movement.created)
	{
		std::shared_ptr<Movement> movement = std::make_shared<Movement>(enemy.getSprite(), componentPresets.find(name)->second->movement.maxVelocity, componentPresets.find(name)->second->movement.acceleration, componentPresets.find(name)->second->movement.deceleration, &enemy);
		enemy.addComponent(movement);
	}
	//2
	if (componentPresets.find(name)->second->animation.created)
	{
		std::shared_ptr<AnimationC> animationComp = std::make_shared<AnimationC>(enemy.getSprite(), *textures.find(name)->second, x, y, &enemy);
		for (int i = 0; i < componentPresets.find(name)->second->animation.numAnimations; i++)
		{
			std::shared_ptr<AnimationPreset> aP = componentPresets.find(name)->second->animation.animations.at(i);
			animationComp->addAnimation(aP->key, aP->animation_timer, aP->start_frame_x, aP->start_frame_y, aP->frames_x, aP->frames_y, aP->width, aP->height);
		}
		enemy.addComponent(animationComp);
		
	}
	//3
	if (componentPresets.find(name)->second->attribute.created)
	{
		std::shared_ptr<Attribute> attribute = std::make_shared<Attribute>(componentPresets.find(name)->second->attribute.level, &enemy);
		enemy.addComponent(attribute);
	}
	//5
	if (componentPresets.find(name)->second->ai.created)
	{
		std::shared_ptr<enemyAi> ai = std::make_shared<enemyAi>(&enemy);
		enemy.addComponent(ai);
	}
	
	return false;
}

void EnemyLibrary::initComponents()
{
	
	//Components
	if (componentDoc.LoadFile("enemyComponent.xml") != tinyxml2::XML_SUCCESS)
	{
		std::cout << "ERROR::EnemyLibrary::COMPONENT XML FILE COULD NOT LOAD \n" << "enemyComponent.xml";
		exit(1);
	}

	tinyxml2::XMLElement* compRoot = componentDoc.FirstChildElement("Map"); //root of xml
	tinyxml2::XMLElement* enemy_1 = compRoot->FirstChildElement("Enemy");
	tinyxml2::XMLElement* component;

	while (enemy_1) { //loops until no more enemies exist
		component = enemy_1->FirstChildElement("Component");
		componentPresets[enemy_1->Attribute("name")] = (componentLibrary.add(component));//adds presets to names of enemies listed in file
	
		enemy_1 = enemy_1->NextSiblingElement();
	}

	


}

std::vector<std::shared_ptr<Enemy>>& EnemyLibrary::getEnemies()
{
	return enemies;
}

ComponentLibrary::ComponentLibrary()
{
	componentTypes["hitbox"] = 0;
	componentTypes["movement"] = 1;
	componentTypes["animation"] = 2;
	componentTypes["attribute"] = 3;
	componentTypes["input"] = 4;
	componentTypes["AI"] = 5;
	componentTypes["skill"] = 6;
	componentTypes["enemyData"] = 7;
	componentTypes["Combat"] = 8;
	componentTypes["item"] = 9;

}

std::shared_ptr<allEnemyPresets> ComponentLibrary::add(tinyxml2::XMLElement* component)
{
	std::shared_ptr<allEnemyPresets> presets = std::make_shared<allEnemyPresets>();
	while (component) {
		if (component->IntAttribute("type") == componentTypes.find("hitbox")->second)//0
			addHitbox(component, presets);
		else if (component->IntAttribute("type") == componentTypes.find("movement")->second)//1
			addMovement(component, presets);
		else if (component->IntAttribute("type") == componentTypes.find("animation")->second)//2
			addAnimation(component, presets);
		else if (component->IntAttribute("type") == componentTypes.find("attribute")->second)//3
			addAttribute(component, presets);
		else if (component->IntAttribute("type") == componentTypes.find("AI")->second)
			addAI(component, presets);
		std::cout << component->IntAttribute("type") << "\n";
		component = component->NextSiblingElement();
	}

	return presets;
}

void ComponentLibrary::addHitbox(tinyxml2::XMLElement* component, std::shared_ptr<allEnemyPresets> presets)
{
	presets->hitBox.created = true;
	component->QueryFloatAttribute("offsetX", &presets->hitBox.offSetX);
	component->QueryFloatAttribute("offsetY", &presets->hitBox.offSetY);
	component->QueryFloatAttribute("width", &presets->hitBox.width);
	component->QueryFloatAttribute("height", &presets->hitBox.height);

}

void ComponentLibrary::addMovement(tinyxml2::XMLElement* component, std::shared_ptr<allEnemyPresets> presets)
{
	presets->movement.created = true;
	component->QueryFloatAttribute("maxVelocity", &presets->movement.maxVelocity);
	component->QueryFloatAttribute("acceleration", &presets->movement.acceleration);
	component->QueryFloatAttribute("deceleration", &presets->movement.deceleration);
}

void ComponentLibrary::addAttribute(tinyxml2::XMLElement* component, std::shared_ptr<allEnemyPresets> presets)
{
	presets->attribute.created = true;
	component->QueryIntAttribute("level", &presets->attribute.level);
}

void ComponentLibrary::addAnimation(tinyxml2::XMLElement* component, std::shared_ptr<allEnemyPresets> presets)
{
	presets->animation.created = true;
	component->QueryIntAttribute("numAnim", &presets->animation.numAnimations);
	tinyxml2::XMLElement* animation_ = component->FirstChildElement("animation");
	presets->animation.animations.reserve(presets->animation.numAnimations);
	for(int i = 0; i < presets->animation.numAnimations; i++)
	{
		presets->animation.animations.push_back(std::make_shared<AnimationPreset>());
		presets->animation.animations.back()->key = animation_->Attribute("key");
		animation_->QueryFloatAttribute("animation_timer", &presets->animation.animations.back()->animation_timer);
		animation_->QueryIntAttribute("start_frame_x", &presets->animation.animations.back()->start_frame_x);
		animation_->QueryIntAttribute("start_frame_y", &presets->animation.animations.back()->start_frame_y);
		animation_->QueryIntAttribute("frames_x", &presets->animation.animations.back()->frames_x);
		animation_->QueryIntAttribute("frames_y", &presets->animation.animations.back()->frames_y);
		animation_->QueryIntAttribute("width", &presets->animation.animations.back()->width);
		animation_->QueryIntAttribute("height", &presets->animation.animations.back()->height);
		animation_ = animation_->NextSiblingElement("animation");
	}
}

void ComponentLibrary::addAI(tinyxml2::XMLElement* component, std::shared_ptr<allEnemyPresets> presets)
{
	presets->ai.created = true;
}
