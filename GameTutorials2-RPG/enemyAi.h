#pragma once
#include "Component.h"

class Movement;

class AISetting;
class enemyAi :
    public Component
{
public:
    enemyAi(std::shared_ptr<Entity> player, bool follow, bool roaming, Entity& owner);
    void update(const float& dt, const sf::Vector2f mousePosView);
    void render(sf::RenderTarget& target, sf::Shader* shader, sf::Vector2f light_position, const bool show_hitbox);
    void reactions(const float& dt);
    void setIdle();
    void setRoaming(bool update_roaming);
    void setFollowing(bool update_roaming);
    void setDeath(bool death);
    void setWalkSpeed(float speed);
    void setAggro(const bool Aggro);
    void setStunned(const bool stunned);
    const float& getWalkSpeed();
    const bool& getDeletable();

private:
    gui::KeyTimeManger keytimer;
    std::map<std::string, bool> OptionsList;
    std::shared_ptr<Entity> entity;
    std::map<std::string, std::shared_ptr<AISetting>> Options;
    Movement* movement;
    float walkSpeed;
    bool following;
    bool aggro;
    bool death;
    bool deletable;

};
