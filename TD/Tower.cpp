#include "Tower.h"
#include "Enemy.h"
#include <cmath>
#include <algorithm>
#include <SFML/Audio.hpp>
#include "SoundManager.h"

Tower::Tower(sf::Vector2f position, TowerType type)
    : m_type(type)
{
    m_shape.setRadius(20.f);
    m_shape.setOrigin({ 20.f, 20.f });
    m_shape.setPosition(position);


    switch (type)
    {
    case TowerType::Basic:
        m_cost = 70;
        m_damage = 25;
        m_range = 160;
        m_fireRate = 1.2f;
        m_shape.setFillColor(sf::Color::Green);
        break;

    case TowerType::Sniper:
        m_cost = 150;
        m_damage = 150;
        m_range = 350;
        m_fireRate = 0.4f;
        m_shape.setFillColor(sf::Color::Magenta);
        break;

    case TowerType::Rapid:
        m_cost = 100;
        m_damage = 12;
        m_range = 130;
        m_fireRate = 5.f;
        m_shape.setFillColor(sf::Color::Cyan);
        break;
    }


}

void Tower::update(float dt, std::vector<Enemy>& enemies)
{
    if (m_destroyed)
        return;

    if (m_isNuclear)
        return;

    m_timer += dt;

    Enemy* target = nullptr;

    for (auto& enemy : enemies)
    {
        if (enemy.isDead())
            continue;

        sf::Vector2f enemyPos = enemy.getPosition();
        sf::Vector2f myPos = m_shape.getPosition();

        float dx = enemyPos.x - myPos.x;
        float dy = enemyPos.y - myPos.y;
        float distance = std::sqrt(dx * dx + dy * dy);

        if (distance <= m_range)
        {
            target = &enemy;
            break;
        }
    }

    if (target && m_timer >= 1.f / m_fireRate)
    {
        m_projectiles.emplace_back(
            m_shape.getPosition(),
            target,
            m_damage
        );

        m_timer = 0.f;
    }


    for (auto& projectile : m_projectiles)
    {
        projectile.update(dt);
    }


    m_projectiles.erase(
        std::remove_if(m_projectiles.begin(), m_projectiles.end(),
            [](Projectile& p)
            {
                return !p.isAlive();
            }),
        m_projectiles.end()
    );
}



void Tower::draw(sf::RenderWindow& window)
{
    window.draw(m_shape);

    for (auto& projectile : m_projectiles)
    {
        projectile.draw(window);
    }
}

bool Tower::contains(sf::Vector2f point) const
{
    return m_shape.getGlobalBounds().contains(point);
}

float Tower::getRange() const
{
    return m_range;
}


Tower::TowerType Tower::getType() const
{
    return m_type;
}

float Tower::getDamage() const
{
    return m_damage;
}

sf::Vector2f Tower::getPosition() const
{
    return m_shape.getPosition();
}

void Tower::upgrade(std::vector<Enemy>& enemies)
{
    

    if (m_isNuclear || m_destroyed)
        return;
    if (m_level >= 10)
        return;

    m_level++;

    // Safe levels
    if (m_level <= 5)
    {
        m_damage *= 1.25f;
        m_range *= 1.1f;
        m_fireRate *= 1.08f;
        return;
    }

    // Unstable levels 6-9
    if (m_level >= 6 && m_level <= 9)
    {
        float explosionChance = 0.1f * (m_level - 5); // 10%,20%,30%,40%

        if ((float)rand() / RAND_MAX < explosionChance)
        {
            explode(enemies);
            return;
        }

        m_damage *= 1.35f;
        m_range *= 1.12f;
        m_fireRate *= 1.1f;
        return;
    }



    // Level 10 = Nuclear unlocked
    if (m_level >= 10)
    {
        m_isNuclear = true;
        m_shape.setFillColor(sf::Color::White);
    }
}

int Tower::getUpgradeCost() const
{
    return static_cast<int>(m_cost * (1 + m_level * 0.8f));
}

int Tower::getLevel() const
{
    return m_level;
}

int Tower::getCost() const
{
    return static_cast<int>(m_cost);
}

bool Tower::isNuclear() const
{
    return m_isNuclear;
}

bool Tower::isDestroyed() const
{
    return m_destroyed;
}

void Tower::triggerNuke(std::vector<Enemy>& enemies)
{
        if (!m_isNuclear || m_destroyed)
            return;

    for (auto& enemy : enemies)
    {
        enemy.kill();
    }

    m_destroyed = true;
}

float Tower::getSacrificeDamage() const
{
    return m_damage * 10.f;
}

void Tower::explode(std::vector<Enemy>& enemies)
{
    SoundManager soundManager;
    float explosionRadius = m_range * 1.5f;
    float explosionDamage = m_damage*10;
    soundManager.playExplosion();

    sf::Vector2f pos = getPosition();

    for (auto& enemy : enemies)
    {
        float dx = enemy.getPosition().x - pos.x;
        float dy = enemy.getPosition().y - pos.y;
        float dist = std::sqrt(dx * dx + dy * dy);

        if (dist <= explosionRadius)
            enemy.takeDamage(explosionDamage);
    }

    m_destroyed = true;
}