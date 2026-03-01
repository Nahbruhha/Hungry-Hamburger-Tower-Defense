#pragma once
#include <SFML/Audio.hpp>

class SoundManager
{
public:
    SoundManager();
    void playEnemyDead();
    void playPlace();
    void playUpgrade();
    void playExplosion();
    void playOver();
    void setMasterVolume(float volume);

private:
    
    float m_masterVolume = 40.f;

    sf::SoundBuffer m_enemyDeadBuffer;
    std::optional<sf::Sound> m_enemyDeadSound;

    sf::SoundBuffer m_placeBuffer;          
    std::optional<sf::Sound> m_placeSound;

    sf::SoundBuffer m_upgradeBuffer;
    std::optional<sf::Sound> m_upgradeSound;

    sf::SoundBuffer m_explodeBuffer;
    std::optional<sf::Sound> m_explodeSound;

    sf::SoundBuffer m_overBuffer;
    std::optional<sf::Sound> m_overSound;
};