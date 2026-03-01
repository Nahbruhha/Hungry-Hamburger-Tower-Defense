#include "Projectile.h"
#include "Enemy.h"
#include <cmath>

Projectile::Projectile(sf::Vector2f startPos, Enemy* target, float damage)
    : m_target(target), m_damage(damage)
{
    m_shape.setRadius(6.f);
    m_shape.setFillColor(sf::Color::Black);
    m_shape.setOrigin({ 6.f, 6.f });
    m_shape.setPosition(startPos);
}

void Projectile::update(float dt)
{
    if (!m_target || m_target->isDead())
    {
        m_alive = false;
        return;
    }

    sf::Vector2f current = m_shape.getPosition();
    sf::Vector2f targetPos = m_target->getPosition();

    sf::Vector2f dir = targetPos - current;

    float length = std::sqrt(dir.x * dir.x + dir.y * dir.y);

    if (length < 5.f)
    {
        m_target->takeDamage(m_damage);
        m_alive = false;
        return;
    }

    dir /= length;
    m_shape.move(dir * m_speed * dt);
}

void Projectile::draw(sf::RenderWindow& window)
{
    if (m_alive)
        window.draw(m_shape);
}

bool Projectile::isAlive() const
{
    return m_alive;
}