#pragma once
#include "ItemComponent.h"

class Bullet;
class TileMap;
class PhysicsDevice;

class RuneComponent :
    public ItemComponent
{
public:

    void initVaribles() {};
    RuneComponent(std::string bullet_texture, Item& owner);

    void updateBulletCollision(const float& dt, std::shared_ptr<TileMap> map);
    virtual void shoot(float playerX, float playerY, float playerVelX, float playerVelY, const unsigned short lastState, std::shared_ptr<PhysicsDevice> p_device);
    virtual void update(const float& dt, const sf::Vector2f& mousePosView, const sf::Vector2f& position);
    virtual void render(sf::RenderTarget& target, sf::Shader* shader = NULL, sf::Vector2f light_position = sf::Vector2f(), const bool show_hitbox = false);
    const bool isBulletEmpty();
private:
    std::vector <std::shared_ptr<Bullet> > bullets;
    sf::Texture bulletTexture;
};

