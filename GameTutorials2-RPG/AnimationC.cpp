#include "stdafx.h"
#include "AnimationC.h"
#include "Entity.h"
#include "Movement.h"

AnimationC::AnimationC(sf::Sprite& sprite, sf::Texture& texture_sheet, float x, float y, Entity* owner)
	: sprite(sprite), textureSheet(texture_sheet), lastAnimation(NULL), priorityAnimation(NULL), Component("animation", owner)
{
	//sets initial sprite pos
	owner->setPosition(x, y);
	//rest of sprite set in animations.

}

AnimationC::~AnimationC()
{
}
//Functions

void AnimationC::addAnimation(
	const std::string key,
	float animationTimer,
	int start_x, int start_y, int end_x, int end_y, int width, int height)
{
	animations[key] = std::make_shared<Animation>(
		sprite, textureSheet,
		animationTimer,
		start_x, start_y, end_x, end_y, width, height
		);
}

const bool& AnimationC::play(const std::string key, const float& dt, const bool priority = false)
{
	if (priorityAnimation) //If there is a priority animation
	{
		if (priorityAnimation == animations[key])
		{
			if (lastAnimation != animations[key])
			{
				if (lastAnimation == NULL)
					lastAnimation = animations[key];
				else
				{
					lastAnimation->reset();
					lastAnimation = animations[key];
				}
			}
			else if(lastAnimation == animations[key] && animations[key]->isDone())
			{
				priorityAnimation = NULL;
			}

			//If the priority animation is done, remove it
			if (animations[key]->play(dt))
			{
				priorityAnimation = NULL;
			}
		}
	}
	else //Play animation of no other priority animation is set
	{
		//If this is a priority animation, set it.
		if (priority)
		{
			priorityAnimation = animations[key];
		}

		if (lastAnimation != animations[key])
		{
			if (lastAnimation == NULL)
				lastAnimation = animations[key];
			else
			{
				lastAnimation->reset();
				lastAnimation = animations[key];
				
			}
		}

		animations[key]->play(dt);
	}

	return animations[key]->isDone();
}

const bool& AnimationC::play(const std::string key, const float& dt, const float& modifier, const float& modifier_max, const bool priority = false)
{
	if (priorityAnimation) //If there is a priority animation
	{
		if (priorityAnimation == animations[key])
		{
			if (lastAnimation != animations[key])
			{
				if (lastAnimation == NULL)
					lastAnimation = animations[key];
				else
				{
					lastAnimation->reset();
					lastAnimation = animations[key];
				}
			}

			//If the priority animation is done, remove it
			if (animations[key]->play(dt, abs(modifier / modifier_max)))
			{
				priorityAnimation = NULL;
			}
		}
	}
	else //Play animation of no other priority animation is set
	{
		//If this is a priority animation, set it.
		if (priority)
		{
			priorityAnimation = animations[key];
		}

		if (lastAnimation != animations[key])
		{
			if (lastAnimation == NULL)
				lastAnimation = animations[key];
			else
			{
				lastAnimation->reset();
				lastAnimation = animations[key];
			}
		}

		animations[key]->play(dt, abs(modifier / modifier_max));
	}

	return animations[key]->isDone();
}

const bool AnimationC::getLastIsDone(const std::string key) const
{
	return animations.at(key)->isDone();
}

void AnimationC::update(const float& dt, const sf::Vector2f mousePosView)
{

}

void AnimationC::render(sf::RenderTarget& target, sf::Shader* shader, sf::Vector2f light_position, const bool show_hitbox)
{
	if (shader) {
		shader->setUniform("hasTexture", true);
		shader->setUniform("lightPos", light_position);

		target.draw(sprite, shader);
	}
	else
	{
		target.draw(sprite);
	}
}

void AnimationC::setIsDone(const std::string key, bool doneStatus)
{
	animations[key]->setDone(doneStatus);
}

const bool& AnimationC::Animation::isDone() const
{
	return done;
}

void AnimationC::Animation::setDone(bool done_status)
{
	done = done_status;
}
