#include "SoundManager.h"
#include <iostream>
#include <filesystem>
#include <algorithm>


SoundManager::SoundManager()
{
    if (!m_enemyDeadBuffer.loadFromFile("EnemyDead.wav"))
    {
        std::cout << "Failed to load EnemyDead.wav\n";
    }
    else
    {
        m_enemyDeadSound.emplace(m_enemyDeadBuffer);
    }

    if (!m_placeBuffer.loadFromFile("Click.wav"))
    {
        std::cout << "Failed to load Click.wav\n";
    }
    else
    {
        m_placeSound.emplace(m_placeBuffer);
    }

    if (!m_upgradeBuffer.loadFromFile("Upgrade.wav"))
    {
        std::cout << "Failed to load Upgrade.wav\n";
    }
    else
    {
        m_upgradeSound.emplace(m_upgradeBuffer);
    }

    if (!m_explodeBuffer.loadFromFile("Explosion.wav"))
    {
        std::cout << "Failed to load Explosion.wav\n";
    }
    else
    {
        m_explodeSound.emplace(m_explodeBuffer);
    }

    if (!m_overBuffer.loadFromFile("Gameover.wav"))
    {
        std::cout << "Failed to load Gameover.wav\n";
    }
    else
    {
        m_overSound.emplace(m_overBuffer);
    }
}

void SoundManager::setMasterVolume(float volume)
{
    m_masterVolume = std::clamp(volume, 0.f, 100.f);
}

void SoundManager::playEnemyDead()
{
    if (m_enemyDeadSound)
        m_enemyDeadSound->play();
        m_enemyDeadSound->setVolume(m_masterVolume*0.3);
}

void SoundManager::playPlace()
{
    if (m_placeSound)
        m_placeSound->play();
        m_placeSound->setVolume(m_masterVolume);
}

void SoundManager::playUpgrade()
{
    if (m_upgradeSound)
        m_upgradeSound->play();
        m_upgradeSound->setVolume(m_masterVolume*1.2);
}

void SoundManager::playExplosion()
{
    if (m_explodeSound)
        m_explodeSound->play();
        m_explodeSound->setVolume(m_masterVolume*1.2);
}

void SoundManager::playOver() {
    if (m_overSound)
        m_overSound->play();
        m_overSound->setVolume(m_masterVolume*0.8);
}