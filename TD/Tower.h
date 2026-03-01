#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Projectile.h"

class Enemy;

class Tower
{
public:

    enum class TowerType
    {
        Basic,
        Sniper,
        Rapid
    };

    Tower(sf::Vector2f position, TowerType type);
        
    float getSacrificeDamage() const;

    void explode(std::vector<Enemy>& enemies);

    bool isNuclear() const;
    bool isDestroyed() const;
    void triggerNuke(std::vector<Enemy>& enemies);
    void update(float dt, std::vector<Enemy>& enemies);
    void draw(sf::RenderWindow& window);
    bool contains(sf::Vector2f point) const;
    float getRange() const;
    sf::Vector2f getPosition() const;

    void upgrade(std::vector<Enemy>& enemies);
    int getUpgradeCost() const;
    int getLevel() const;
    int getCost() const;
    TowerType getType() const;
    float getDamage() const;

    

private:
    sf::CircleShape m_shape;

    float m_cost;
    float m_damage;
    float m_range;
    float m_fireRate;
    float m_timer = 0.f;
    int m_level = 1;
    bool m_isNuclear = false;
    bool m_destroyed = false;
    TowerType m_type;
    

    std::vector<Projectile> m_projectiles;
};