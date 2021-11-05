#pragma once
#include "Component.h"

class progressBar;

class enemyGui :
    public Component
{
public:
    enemyGui(Entity& Owner, sf::Font& font, sf::VideoMode& vm);

    void update(const float& dt, const sf::Vector2f mousePosView);
    void render(sf::RenderTarget& target, sf::Shader* shader, sf::Vector2f light_position, const bool show_hitbox = false);
    void setHidden(bool hidden);

private:
    std::unique_ptr<gui::progressBar> healthBar;
    sf::Font& font;
    sf::VideoMode& vm;
    float tempPercent;
    float width;
    float height;
    bool hidden;
};

