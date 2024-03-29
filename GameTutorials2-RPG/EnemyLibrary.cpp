#include "stdafx.h"
#include "EnemyLibrary.h"
#include "ComponentInclude.h"
#include "Presets.h"
#include "TileMap.h"
#include "TextTagSystem.h"
#include "StateData.h"
#include "GraphicsSettings.h"

//Take in a File
EnemyLibrary::EnemyLibrary(std::shared_ptr<TextTagSystem> textts, std::shared_ptr<Entity> player)
	: tts(textts), decreaseSpawn(false), player(player)
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

	initComponents();
}

std::shared_ptr<sf::Texture> EnemyLibrary::find(std::string name)
{
	return textures.find(name)->second;
}


void EnemyLibrary::initStateData(StateData& state_data)
{
	stateData = std::make_shared<StateData>(state_data);
}

void EnemyLibrary::initGraph(std::shared_ptr<Graph> graph, std::shared_ptr<std::vector<sf::Vector2i>> obstacles)
{
	this->graph = graph;
	this->obstacles = obstacles;
}

void EnemyLibrary::update(const float& dt, bool playerAttack, std::shared_ptr<Entity> attacker, std::shared_ptr<TileMap> map)
{


	if (!enemies.empty()) {
		auto i = enemies.begin();
		while (i != enemies.end())
		{
			i->get()->update(dt);
			//IsDead
			if (i->get()->getComponent<Attribute>()->isDead()) {
				i->get()->getComponent<enemyAi>()->setDeath(true);
			
				if (i->get()->getComponent<enemyAi>()->getDeletable()) {
					decreaseSpawn = true;
					int exp = attacker->getComponent<Combat>()->expHandler(i->get()->getComponent<EnemyData>()->expWorth, i->get()->getComponent<Attribute>()->level);
					this->tts->addTextTag(EXPERIENCE_TAG, attacker->getPosition().x - 40.f, attacker->getPosition().y - 30.f, exp, "+", " exp");
					i = enemies.erase(i);
				}else
				{
					++i;
				}
			}
			else if (i->get()->getComponent<EnemyData>()->getName() == "despawned")//make check for despawn
			{
				i->get()->getComponent<Attribute>()->hp = 0;
			}
			else
			{
				


			if (playerAttack)
				if (i->get()->getDistance(*player) < player->getComponent<Attribute>()->range)
				{
					
					int dmg = i->get()->getComponent<Combat>()->defend(*player);
					tts->addTextTag(NEGATIVE_TAG, i->get()->getPosition().x, i->get()->getPosition().y, dmg, "", "");
				}
			
			//Collison
			//map->updateWorldBounds(std::make_shared<Entity>(*i->get()));
			//->updateTileCollision(std::make_shared<Entity>(*i->get()), dt);

			//AI
			if (i->get()->getDistance(*player) < i->get()->getComponent<Attribute>()->range)
			{
				i->get()->getComponent<enemyAi>()->setAggro(true);
				
				
			}else
			{
				i->get()->getComponent<enemyAi>()->setAggro(false);
				i->get()->getComponent<enemyAi>()->setRoaming(true);
			}

			
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

bool EnemyLibrary::createComponents(std::shared_ptr<Entity> enemy, std::string name, std::shared_ptr<EnemySpawner> spawner)
{


	bool anyCreated = false;
	
	//2
	if (componentPresets.find(name)->second->animation.created)
	{
		std::shared_ptr<AnimationC> animationComp = std::make_shared<AnimationC>(enemy->getSprite(), *textures.find(name)->second, spawner->getPosition().x, spawner->getPosition().y, *enemy);
		for (int i = 0; i < componentPresets.find(name)->second->animation.numAnimations; i++)
		{
			std::shared_ptr<AnimationPreset> aP = componentPresets.find(name)->second->animation.animations.at(i);
			animationComp->addAnimation(aP->key, aP->animation_timer, aP->start_frame_x, aP->start_frame_y, aP->frames_x, aP->frames_y, aP->width, aP->height);
		}
		enemy->addComponent(animationComp);
		anyCreated = true;
		
	}

	//0
	if (componentPresets.find(name)->second->physics.created)
	{
		std::shared_ptr<physicsComponent> physicsC = std::make_shared<physicsComponent>(componentPresets.find(name)->second->physics.gamePhysics, player->getComponent<physicsComponent>()->pDevice, *enemy);
		enemy->addComponent(physicsC);
		anyCreated = true;
	}


	//1
	if (componentPresets.find(name)->second->movement.created)
	{
		std::shared_ptr<Movement> movement = std::make_shared<Movement>(enemy->getSprite(), componentPresets.find(name)->second->movement.maxVelocity, componentPresets.find(name)->second->movement.acceleration, componentPresets.find(name)->second->movement.deceleration, *enemy);
		enemy->addComponent(movement);
		anyCreated = true;
	}
	//3
	if (componentPresets.find(name)->second->attribute.created)
	{
		std::shared_ptr<Attribute> attribute = std::make_shared<Attribute>(componentPresets.find(name)->second->attribute.level, *enemy);

		attribute->range = componentPresets.find(name)->second->attribute.range;

		for (int i = 0; i < spawner->enemyLevel - 1; i++)
		{
			attribute->levelUp();
		}

		attribute->randomAssignment();
		attribute->updateStats(true);
		enemy->addComponent(attribute);
		anyCreated = true;
	}
	//7
	if (componentPresets.find(name)->second->enemyData.created)
	{
		std::shared_ptr<enemyDataPreset> eP = std::make_shared<enemyDataPreset>(componentPresets.find(name)->second->enemyData);
		std::shared_ptr<EnemyData> data = std::make_shared<EnemyData>(eP->enemyName, EnemyPowerLevel::NORMAL, eP->expMult, eP->vitalityMult, eP->strengthMult, eP->dexterityMult, eP->agilityMult, eP->intellegenceMult, nullptr, spawner, *enemy);
		enemy->addComponent(data);
		anyCreated = true;
	}
	//5
	if (componentPresets.find(name)->second->ai.created)
	{
		std::shared_ptr<enemyAi> ai = std::make_shared<enemyAi>(player, componentPresets.find(name)->second->ai.follow, true, *enemy);
		enemy->addComponent(ai);
		anyCreated = true;
	}
	sf::VideoMode& vm = stateData->GraphicsSettings->resolution;
	std::shared_ptr<enemyGui> enmyGui = std::make_shared<enemyGui>(*enemy, *stateData->font, vm);
	enemy->addComponent(enmyGui);
	if (componentPresets.find(name)->second->combat.created)
	{
		std::shared_ptr<Combat> combat = std::make_shared<Combat>(*enemy);
		enemy->addComponent(combat);
	}
	

	return anyCreated;
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
	componentTypes["userInput"] = 4;
	componentTypes["AI"] = 5;
	componentTypes["skill"] = 6;
	componentTypes["enemyData"] = 7;
	componentTypes["combat"] = 8;
	componentTypes["item"] = 9;
	componentTypes["physics"] = 10;

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
		else if (component->IntAttribute("type") == componentTypes.find("AI")->second) //5
			addAI(component, presets);
		else if (component->IntAttribute("type") == componentTypes.find("enemyData")->second) //7
			addEnemyData(component, presets);
		else if (component->IntAttribute("type") == componentTypes.find("combat")->second) //8
			addCombat(component, presets);
		else if (component->IntAttribute("type") == componentTypes.find("physics")->second) //10
			addPhysics(component, presets);
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
	component->QueryFloatAttribute("maxVelocity", &presets->movement.maxVelocity.x);
	component->QueryFloatAttribute("maxVelocity", &presets->movement.maxVelocity.y);
	component->QueryFloatAttribute("acceleration", &presets->movement.acceleration.x);
	component->QueryFloatAttribute("acceleration", &presets->movement.acceleration.y);
	component->QueryFloatAttribute("deceleration", &presets->movement.deceleration.x);
	component->QueryFloatAttribute("deceleration", &presets->movement.deceleration.y);
}

void ComponentLibrary::addAttribute(tinyxml2::XMLElement* component, std::shared_ptr<allEnemyPresets> presets)
{
	presets->attribute.created = true;
	component->QueryIntAttribute("level", &presets->attribute.level);
	component->QueryIntAttribute("range", &presets->attribute.range);
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

void ComponentLibrary::addCombat(tinyxml2::XMLElement*, std::shared_ptr<allEnemyPresets> presets)
{
	presets->combat.created = true;
}

void ComponentLibrary::addEnemyData(tinyxml2::XMLElement* component, std::shared_ptr<allEnemyPresets> presets)
{
	presets->enemyData.created = true;
	presets->enemyData.enemyName = component->Attribute("enemyName");
	component->QueryIntAttribute("enemyPowerLevel", &presets->enemyData.enemyPowerLevel);
	component->QueryFloatAttribute("exp_mult", &presets->enemyData.expMult);
	component->QueryFloatAttribute("vitalityMultiplier", &presets->enemyData.vitalityMult);
	component->QueryFloatAttribute("strengthMultiplier", &presets->enemyData.strengthMult);
	component->QueryFloatAttribute("dexterityMultiplier", &presets->enemyData.dexterityMult);
	component->QueryFloatAttribute("agilityMultiplier", &presets->enemyData.agilityMult);
	component->QueryFloatAttribute("intellgenceMultiplier", &presets->enemyData.intellegenceMult);
}

void ComponentLibrary::addPhysics(tinyxml2::XMLElement* component, std::shared_ptr<allEnemyPresets> presets)
{
	presets->physics.created = true;
	presets->physics.gamePhysics.category = CATEGORY_ENEMY;
	presets->physics.gamePhysics.mask = MASK_ENEMY;
	component->QueryIntAttribute("bodyType", (int*)&presets->physics.gamePhysics.bodyType);
	component->QueryIntAttribute("objectShape", (int*)&presets->physics.gamePhysics.objectShape);
	component->QueryFloatAttribute("width", &presets->physics.gamePhysics.width);
	component->QueryFloatAttribute("height", &presets->physics.gamePhysics.height);
	component->QueryFloatAttribute("density", &presets->physics.gamePhysics.density);
	component->QueryFloatAttribute("friction", &presets->physics.gamePhysics.friction);
	component->QueryFloatAttribute("restitution", &presets->physics.gamePhysics.restitution);
	component->QueryFloatAttribute("angularDamping", &presets->physics.gamePhysics.angularDamping);
	component->QueryFloatAttribute("linearDamping", &presets->physics.gamePhysics.linearDamping);
	component->QueryFloatAttribute("force", &presets->physics.gamePhysics.force);
	component->QueryFloatAttribute("angle", &presets->physics.gamePhysics.angle);
	component->QueryFloatAttribute("spinSpeed", &presets->physics.gamePhysics.spinSpeed);
	component->QueryBoolAttribute("bullet", &presets->physics.gamePhysics.bullet);
	component->QueryBoolAttribute("physicsOn", &presets->physics.gamePhysics.physicsOn);

}

void ComponentLibrary::addAI(tinyxml2::XMLElement* component, std::shared_ptr<allEnemyPresets> presets)
{
	presets->ai.created = true;
	component->QueryBoolAttribute("follow", &presets->ai.follow);
}
