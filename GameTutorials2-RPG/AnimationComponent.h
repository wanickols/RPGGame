#pragma once

namespace sf {
	class Texture;
	class Sprite;
}

class AnimationComponent
{
public:
	AnimationComponent(sf::Sprite& sprite, sf::Texture& texture_sheet);
	virtual ~AnimationComponent();

	//Functions
	void addAnimation(
		const std::string key,
		float animationTimer,
		int start_x, int start_y, int end_x, int end_y, int width, int height);

	const bool& play(const std::string key, const float& dt, const bool priority);
	const bool& play(const std::string key, const float& dt, const float& modifier, const float& modifier_max, const bool priority);
	const bool getLastIsDone(const std::string key) const;
private:
	class Animation {
	public:
		//variables
		sf::Sprite& sprite;
		sf::Texture& textureSheet;
		float animationTimer;
		float timer;
		bool done;
		int width;
		int height;
		sf::IntRect startRect;
		sf::IntRect currRect;
		sf::IntRect endRect;

		Animation(sf::Sprite& sprite, sf::Texture& texture_sheet, float animation_timer, int start_frame_x, int start_frame_y, int frames_x, int frames_y, int width, int height)
			: sprite(sprite), textureSheet(texture_sheet), animationTimer(animation_timer), width(width), height(height), done(false)
		{
			timer = 0.f;
			startRect = sf::IntRect(start_frame_x * width, start_frame_y * height, width, height);
			currRect = startRect;
			endRect = sf::IntRect(frames_x * width, frames_y * height, width, height);

			sprite.setTexture(textureSheet, true);
			sprite.setTextureRect(startRect);
		}

		//Accessors
		const bool& isDone() const;

		//functions

		const bool& play(const float& dt) {
			timer += 100.f * dt;
			if (timer >= animationTimer)
			{
				timer = 0.f;
				//Animate
				if (currRect != endRect)
				{
					currRect.left += width;
				}
				else //reset
				{
					currRect.left = startRect.left;
					done = true;
				}
				sprite.setTextureRect(currRect);
			}
			return done;
		}//Normal play
		const bool& play(const float& dt, float mod_percent) {

			if (mod_percent < 0.25f)
				mod_percent = 0.25f;

			timer += mod_percent * 100.f * dt;
			if (timer >= animationTimer)
			{
				timer = 0.f;
				//Animate
				if (currRect != endRect)
				{
					currRect.left += width;
				}
				else //reset
				{
					currRect.left = startRect.left;
					done = true;
				}
				sprite.setTextureRect(currRect);
			}
			return done;
		}//Modifier play function

		void reset() {
			timer = animationTimer;
			currRect = startRect;
		}

	};

	sf::Sprite& sprite;
	sf::Texture& textureSheet;

	std::map<std::string, std::shared_ptr<Animation>> animations;
	std::shared_ptr<Animation> lastAnimation;
	std::shared_ptr<Animation> priorityAnimation;
	//functions

};

