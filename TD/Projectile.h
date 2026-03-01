#pragma once
#include <SFML/Graphics.hpp>

class Enemy;

class Projectile
{
public:
    Projectile(sf::Vector2f startPos, Enemy* target, float damage);

    void update(float dt);
    void draw(sf::RenderWindow& window);
    bool isAlive() const;

private:
    sf::CircleShape m_shape;
    Enemy* m_target;
    float m_speed = 400.f;
    float m_damage;
    bool m_alive = true;
};