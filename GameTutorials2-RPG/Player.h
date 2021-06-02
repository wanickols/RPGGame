#pragma once
#include "Entity.h"
class Player :
    public Entity
{
private:
    //Init Functions
    void initVariables();
    void initComponents();
public:
    Player() = delete;
    Player(float x, float y, sf::Texture& texture);
    virtual ~Player();
    virtual void update(const float& dt);
private:
    //variables
    bool attacking;
    //Functions
    void updateAnimation(const float& dt);
};

