#pragma once
#include <SFML/Graphics.hpp>
#include <vector>


class Enemy
{
public:
    enum class Type
    {
        Normal,
        Fast,
        Tank,
        Boss
    };

    Enemy(const std::vector<sf::Vector2f>& path, Type type, int wave);

    void update(float dt);
    void draw(sf::RenderWindow& window);

    bool isDead() const;
    bool reachedEnd() const;
    void takeDamage(float amount);
    sf::Vector2f getPosition() const;
    int getReward() const { return m_reward; }
    void kill();

private:
    const std::vector<sf::Vector2f>* m_path;
    size_t m_currentIndex = 0;

    float m_speed;
    float m_hp;
    float m_maxHp;

    bool m_isDead = false;
    bool m_reachedEnd = false;

    Type m_type;
    int m_reward = 0;

    sf::CircleShape m_shape;

};
