#pragma once
//Have to include these so all entities have them. Elsewise, you'd have to do it in each cpp;
class Component;

namespace sf {
	class Texture;
	class Sprite;
	class RenderTarget;
}

class Entity
{
private:
	void initVariables();

public:
	Entity();
	virtual ~Entity();

	//component functions
	void setTexture(sf::Texture& texture);

	//template class to get any component
	template<class T>
	T* getComponent()
	{
		for (auto comp : components)
		{
			T* target = nullptr;
			if (target = dynamic_cast<T*>(comp.get()))
			{
				return target;
			}
		}
		return (nullptr);
	}
	
	const virtual sf::Vector2f& getPosition();
	const virtual float getDistance(Entity& entity);
	const virtual sf::Vector2f getCenterPosition();
	const virtual sf::Vector2i getGridPosition(const int& gridSizeI);
	const sf::FloatRect& getNextPositionBounds(const float& dt);
	
	void addComponent(std::shared_ptr<Component> component);

	


	const sf::FloatRect getGlobalBounds();

	virtual void setPosition(float x, float y);
	virtual void setNextPosition(float x, float y);

	//functions
	virtual void move(const float x, const float y, const float& dt, bool player = false);
	virtual void stopVelocity();
	virtual void stopVelocityX();
	virtual void stopVelocityY();

	virtual void update(const float& dt, const sf::Vector2f mousePosView);
	virtual void render(sf::RenderTarget& target, sf::Shader* shader, sf::Vector2f light_position, const bool show_hitbox);
protected:


	//Components
	std::vector<std::shared_ptr<Component>> components;;
	std::map<std::string, bool> componentList;
	sf::Sprite sprite;
private:
	sf::Vector2i gridPosition;
};

