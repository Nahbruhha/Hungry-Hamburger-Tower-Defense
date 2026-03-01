#include "Enemy.h"
#include <cmath>

Enemy::Enemy(const std::vector<sf::Vector2f>& path, Type type, int wave)
    : m_path(&path), m_type(type)
{
    switch (m_type)
    {
    case Type::Normal:
        m_speed = 100.f;
        m_hp = 100;
        m_maxHp = 100;
        m_reward = m_hp/5;
        m_shape.setFillColor(sf::Color::Red);
        break;

    case Type::Fast:
        m_speed = 180.f;
        m_hp = 60;
        m_maxHp = 60;
        m_reward = m_hp/5;
        m_shape.setFillColor(sf::Color::Yellow);
        break;

    case Type::Tank:
        m_speed = 60.f;
        m_hp = 250;
        m_maxHp = 250;
        m_reward = m_hp/5;
        m_shape.setFillColor(sf::Color::Blue);
        break;

    case Type::Boss:
        m_speed = 50.f;
        m_hp = 2000;
        m_maxHp = 2000;
        m_reward = m_hp/5;
        m_shape.setFillColor(sf::Color(150, 0, 150));
        m_shape.setRadius(35.f);
        m_shape.setOrigin({ 35.f, 35.f });
        break;
    }


    float hpMultiplier = 1.f + (wave - 1) * 0.18f;
    float speedMultiplier = 1.f + (wave - 1) * 0.03f;

    m_hp *= hpMultiplier;
    m_speed *= speedMultiplier;

    m_maxHp = m_hp;

    m_shape.setRadius(20.f);
    m_shape.setOrigin({ 20.f, 20.f });
    m_shape.setPosition((*m_path)[0]);
}

void Enemy::update(float dt)
{
    if (m_currentIndex >= m_path->size() - 1)
    {
        m_reachedEnd = true;
        return;
    }

    sf::Vector2f currentPos = m_shape.getPosition();
    sf::Vector2f target = (*m_path)[m_currentIndex + 1];

    sf::Vector2f direction = target - currentPos;

    float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);

    if (length != 0)
        direction /= length;

    m_shape.move(direction * m_speed * dt);

    if (std::hypot(target.x - currentPos.x, target.y - currentPos.y) < 5.f)
    {
        m_currentIndex++;
    }
}

sf::Vector2f Enemy::getPosition() const
{
    return m_shape.getPosition();
}

void Enemy::kill()
{
    m_isDead = true;
}

void Enemy::draw(sf::RenderWindow& window)
{
    window.draw(m_shape);

    
    float barWidth = 40.f;
    float barHeight = 6.f;

    float hpPercent = m_hp / m_maxHp;

    sf::RectangleShape backgroundBar(sf::Vector2f(barWidth, barHeight));
    backgroundBar.setFillColor(sf::Color(60, 60, 60));
    backgroundBar.setPosition(
        sf::Vector2f(
            m_shape.getPosition().x - barWidth / 2.f,
            m_shape.getPosition().y - 35.f
        )
    );

    sf::RectangleShape hpBar(sf::Vector2f(barWidth * hpPercent, barHeight));
    if (hpPercent > 0.6f)
        hpBar.setFillColor(sf::Color::Green); 
    else if (hpPercent > 0.3f)
        hpBar.setFillColor(sf::Color::Yellow);
    else
        hpBar.setFillColor(sf::Color::Red);
    hpBar.setPosition(backgroundBar.getPosition());

    window.draw(backgroundBar);
    window.draw(hpBar);
}

bool Enemy::isDead() const
{
    return m_isDead;
}

bool Enemy::reachedEnd() const
{
    return m_reachedEnd;
}

void Enemy::takeDamage(float amount)
{
    m_hp -= amount;

    if (m_hp <= 0)
        m_isDead = true;
}
