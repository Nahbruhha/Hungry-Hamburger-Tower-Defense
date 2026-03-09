#include <SFML/Graphics.hpp>
#include "Grid.h"
#include "Enemy.h"
#include "Tower.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include "SoundManager.h"

void saveScore(int score)
{
    std::ofstream file("leaderboard.txt", std::ios::app);
    file << score << "\n";
}

std::vector<int> loadScores()
{
    std::vector<int> scores;
    std::ifstream file("leaderboard.txt");
    int s;

    while (file >> s)
        scores.push_back(s);

    std::sort(scores.begin(), scores.end(), std::greater<int>());

    if (scores.size() > 5)
        scores.resize(5);

    return scores;
}

enum class GameState
{
    Menu,
    Playing,
    GameOver
};



int main()
{

    SoundManager soundManager;

    float topScores;
    GameState gameState = GameState::Menu;
    int score = 0;

    sf::Font font;
    if (!font.openFromFile("arial.ttf"))
    {
        return -1;
    }


    int playerHP = 10;
    int gold = 300;
    const int TILE_SIZE = 64;
    const int ROWS = 15;
    const int COLS = 20;

    sf::Text scoreText(font);
    scoreText.setCharacterSize(24);
    scoreText.setPosition({ 10.f, 100.f });

    sf::Text hpText(font);
    sf::Text goldText(font);
    sf::Text waveText(font);

    hpText.setCharacterSize(24);
    goldText.setCharacterSize(24);
    waveText.setCharacterSize(24);





    

    sf::RenderWindow window(sf::VideoMode({ COLS * TILE_SIZE, ROWS * TILE_SIZE }),
        "Hungry Hamburger Tower Defense", sf::Style::Titlebar | sf::Style::Close);

    sf::Text basicText(font), sniperText(font), rapidText(font);

    basicText.setCharacterSize(18);
    sniperText.setCharacterSize(18);
    rapidText.setCharacterSize(18);

    basicText.setString("[Z] Basic - $70");
    sniperText.setString("[X] Sniper - $150");
    rapidText.setString("[C] Rapid - $100");

    basicText.setPosition({ 20.f, window.getSize().y - 100.f });
    sniperText.setPosition({20.f, window.getSize().y - 70.f});
    rapidText.setPosition({ 20.f, window.getSize().y - 40.f });

    

    sf::Text titleText(font);
    titleText.setCharacterSize(60);
    titleText.setString("Hungry Hamburger Tower Defense");
    titleText.setPosition({ 350.f, 200.f });

    sf::RectangleShape startButton({ 300.f, 80.f });
    startButton.setPosition({ 350.f, 350.f });
    startButton.setFillColor(sf::Color(100, 200, 100));

    sf::Text startText(font);
    startText.setCharacterSize(30);
    startText.setString("Start Game");
    startText.setPosition({ 430.f, 350.f });

    sf::RectangleShape topBar;
    topBar.setSize({ window.getSize().x * 1.f, 80.f });
    topBar.setFillColor(sf::Color(30, 30, 30));
    topBar.setPosition({ 0.f, 0.f });
        
    sf::Vector2u windowSize = window.getSize();
    sf::FloatRect titleBounds = titleText.getLocalBounds();
    titleText.setOrigin({ titleBounds.size.x / 2.f, titleBounds.size.y / 2.f });
    titleText.setPosition({ windowSize.x / 2.f, 200.f });
    
    startButton.setOrigin({
        startButton.getSize().x / 2.f,
        startButton.getSize().y / 2.f
        });

    startButton.setPosition({ windowSize.x / 2.f, 400.f });
    sf::FloatRect startTextBounds = startText.getLocalBounds();
    startText.setOrigin({
        startTextBounds.size.x / 2.f,
        startTextBounds.size.y / 2.f + 10.f
        });

    startText.setPosition({
        startButton.getPosition().x,
        startButton.getPosition().y
        });


    


    sf::RectangleShape rightPanel;
    rightPanel.setSize({ 250.f, window.getSize().y * 1.f });
    rightPanel.setFillColor(sf::Color(25, 25, 25));
    rightPanel.setPosition({ window.getSize().x - 250.f, 0.f });

    hpText.setPosition({ 20.f, 20.f });
    goldText.setPosition({ 200.f, 20.f });
    waveText.setPosition({ 400.f, 20.f });
    scoreText.setPosition({ 600.f, 20.f });

    Grid grid(ROWS, COLS, TILE_SIZE);
    grid.createFixedPath();
    std::vector<Enemy> enemies;

    std::vector<Tower> towers;
    int selectedTowerIndex = -1;
    
    enum class BuildMode
    {
        None,
        Basic,
        Sniper,
        Rapid
    };

    BuildMode currentBuildMode = BuildMode::None;

    Tower::TowerType previewType;
    sf::CircleShape previewShape;
    sf::CircleShape previewRange;

    int wave = 1;
    int enemiesToSpawn = 5;
    float spawnTimer = 0.f;
    float spawnDelay = 1.f;

    sf::RectangleShape upgradeButton({ 120.f, 40.f });
    upgradeButton.setFillColor(sf::Color::White);
    upgradeButton.setPosition({
    window.getSize().x - 250.f, 250.f
        });

    sf::Text upgradeText(font);
    upgradeText.setCharacterSize(20);
    upgradeText.setFillColor(sf::Color::Black);

    sf::Text upgradeCostText(font);
    upgradeCostText.setCharacterSize(16);
    upgradeCostText.setFillColor(sf::Color::Black);

    sf::Clock clock;
    
    
    while (window.isOpen()){

        scoreText.setString("Score: " + std::to_string(score));

        float dt = clock.restart().asSeconds();
        spawnTimer += dt;

        while (auto event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();

            if (gameState == GameState::Menu)
            {
                sf::Vector2i mousePixel = sf::Mouse::getPosition(window);
                sf::Vector2f worldPos = window.mapPixelToCoords(mousePixel);

                if (startButton.getGlobalBounds().contains(worldPos))
                {
                    startButton.setFillColor(sf::Color(120, 120, 120));
                }
                else
                {
                    startButton.setFillColor(sf::Color(100, 200, 100));
                }
                    
                if (event->is<sf::Event::MouseButtonPressed>())
                {
                    
                    if (event->getIf<sf::Event::MouseButtonPressed>()->button ==
                        sf::Mouse::Button::Left)
                    {
                        sf::Vector2i mousePixel = sf::Mouse::getPosition(window);
                        sf::Vector2f worldPos = window.mapPixelToCoords(mousePixel);

                        if (startButton.getGlobalBounds().contains(worldPos))
                        {
                            gameState = GameState::Playing;

                            
                            playerHP = 10;
                            gold = 300;
                            score = 0;
                            wave = 1;
                            enemiesToSpawn = 5;
                            enemies.clear();
                            towers.clear();
                            selectedTowerIndex = -1;
                        }
                    }
                }
            }

            
            if (gameState == GameState::GameOver &&
                event->is<sf::Event::KeyPressed>() &&
                event->getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::R)
            {
                gameState = GameState::Playing;
                playerHP = 10;
                gold = 300;
                score = 0;
                wave = 1;
                enemiesToSpawn = 5;
                enemies.clear();
                towers.clear();
                selectedTowerIndex = -1;
                continue;
            }

            
            if (gameState != GameState::Playing)
                continue;

            
            if (event->is<sf::Event::KeyPressed>())
            {
                auto key = event->getIf<sf::Event::KeyPressed>()->code;

                if (key == sf::Keyboard::Key::Z)
                    currentBuildMode = BuildMode::Basic;

                if (key == sf::Keyboard::Key::X)
                    currentBuildMode = BuildMode::Sniper;

                if (key == sf::Keyboard::Key::C)
                    currentBuildMode = BuildMode::Rapid;

                if (key == sf::Keyboard::Key::Escape)
                    currentBuildMode = BuildMode::None;

                if (key == sf::Keyboard::Key::F && selectedTowerIndex != -1)
                {
                    Tower& tower = towers[selectedTowerIndex];

                    if (tower.isNuclear())
                    {
                        soundManager.playExplosion();
                        tower.triggerNuke(enemies);
                    }
                    else
                    {
                        sf::Vector2f pos = tower.getPosition();
                        float range = tower.getRange();
                        float damage = tower.getSacrificeDamage();
                        soundManager.playExplosion();

                        for (auto& enemy : enemies)
                        {
                            float dx = enemy.getPosition().x - pos.x;
                            float dy = enemy.getPosition().y - pos.y;
                            float dist = std::sqrt(dx * dx + dy * dy);

                            if (dist <= range)
                                enemy.takeDamage(damage);
                        }

                        towers.erase(towers.begin() + selectedTowerIndex);
                        selectedTowerIndex = -1;
                    }
                }
            }

            
            if (event->is<sf::Event::MouseButtonPressed>())
            {
                
                if (event->getIf<sf::Event::MouseButtonPressed>()->button ==
                    sf::Mouse::Button::Left)
                {
                    sf::Vector2i mousePixel = sf::Mouse::getPosition(window);
                    sf::Vector2f worldPos = window.mapPixelToCoords(mousePixel);

                    
                    if (selectedTowerIndex != -1 &&
                        upgradeButton.getGlobalBounds().contains(worldPos))
                    {
                        int cost = towers[selectedTowerIndex].getUpgradeCost();

                        if (gold >= cost)
                        {

                            soundManager.playUpgrade();
                            gold -= cost;
                            
                            towers[selectedTowerIndex].upgrade(enemies);
                        }

                        break;
                    }

                    int clickedIndex = -1;

                    for (int i = 0; i < towers.size(); i++)
                    {
                        if (towers[i].contains(worldPos))
                        {
                            clickedIndex = i;
                            break;
                        }
                    }

                    if (clickedIndex != -1)
                    {
                        selectedTowerIndex = clickedIndex;
                        break;
                    }

                    
                    selectedTowerIndex = -1;


                    
                    if (currentBuildMode != BuildMode::None)
                    {
                        sf::Vector2i cell = grid.getCellFromPixel(mousePixel);

                        if (grid.isValidCell(cell.x, cell.y) &&
                            grid.getTile(cell.x, cell.y) == Grid::TileType::Empty)
                        {
                            sf::Vector2f pos(
                                cell.y * TILE_SIZE + TILE_SIZE / 2.f,
                                cell.x * TILE_SIZE + TILE_SIZE / 2.f
                            );

                            Tower::TowerType type =
                                currentBuildMode == BuildMode::Basic ? Tower::TowerType::Basic :
                                currentBuildMode == BuildMode::Sniper ? Tower::TowerType::Sniper :
                                Tower::TowerType::Rapid;

                            Tower newTower(pos, type);

                            bool occupied = false;

                            for (const auto& tower : towers)
                            {
                                if (tower.getPosition() == pos)
                                {
                                    occupied = true;
                                    break;
                                }
                            }

                            if (!occupied && gold >= newTower.getCost())
                            {
                                gold -= newTower.getCost();
                                soundManager.playPlace();
                                towers.push_back(newTower);
                            }



                            currentBuildMode = BuildMode::None;
                        }
                    }
                }
            }
        }

        
        
        if (gameState == GameState::Playing) 
        {

            window.draw(topBar);
            window.draw(hpText);
            window.draw(goldText);
            window.draw(waveText);
            window.draw(scoreText);

            if (currentBuildMode != BuildMode::None)
            {
                sf::Vector2i mousePixel = sf::Mouse::getPosition(window);
                sf::Vector2f worldPos = window.mapPixelToCoords(mousePixel);

                sf::Vector2i cell = grid.getCellFromPixel(mousePixel);

                if (grid.isValidCell(cell.x, cell.y))
                {
                    sf::Vector2f snappedPos(
                        cell.y * TILE_SIZE + TILE_SIZE / 2.f,
                        cell.x * TILE_SIZE + TILE_SIZE / 2.f
                    );

                    previewShape.setRadius(20.f);
                    previewShape.setOrigin({ 20.f, 20.f });
                    previewShape.setPosition(snappedPos);

                    previewRange.setOrigin({ previewRange.getRadius(), previewRange.getRadius() });
                    previewRange.setPosition(snappedPos);

                    bool valid = (grid.getTile(cell.x, cell.y) == Grid::TileType::Empty);

                    if (valid)
                        previewShape.setFillColor(sf::Color(0, 255, 0, 150));
                    else
                        previewShape.setFillColor(sf::Color(255, 0, 0, 150));
                }
            }

            if (enemiesToSpawn > 0 && spawnTimer >= spawnDelay)
            {
                Enemy::Type type;

                if (wave % 5 == 0)
                {
                    type = Enemy::Type::Boss;
                }
                else
                {
                    int randomType = rand() % 3;

                    if (randomType == 0)
                        type = Enemy::Type::Normal;
                    else if (randomType == 1)
                        type = Enemy::Type::Fast;
                    else
                        type = Enemy::Type::Tank;
                }
                enemies.emplace_back(grid.getPath(), type, wave);

                spawnTimer = 0.f;
                enemiesToSpawn--;
            }

            for (auto& enemy : enemies)
            {
                enemy.update(dt);
            }

            enemies.erase(
                std::remove_if(enemies.begin(), enemies.end(),
                    [&](Enemy& e)
                    {
                        
                            if (e.isDead())
                            {
                                gold += e.getReward();
                                score += e.getReward() * 10;
                                soundManager.playEnemyDead();
                                return true;
                            }
                        

                        if (e.reachedEnd())
                        {
                            playerHP--;
                            
                            return true;
                        }

                        return false;
                    }),
                enemies.end()
            );
            
            if (playerHP <= 0)
            {
                soundManager.playOver();
                gameState = GameState::GameOver;
                saveScore(score);
            }

            if (enemies.empty() && enemiesToSpawn == 0)
            {
                wave++;

                if (wave % 5 == 0)
                {
                    enemiesToSpawn = 1;
                }
                else
                {
                    enemiesToSpawn = 5 + wave * 2;
                }

                score += wave * 100;
            }

            if (playerHP <= 0 && gameState == GameState::Playing)
            {
                gameState = GameState::GameOver;
                saveScore(score);
            }

            hpText.setString("HP: " + std::to_string(playerHP));
            goldText.setString("Gold: " + std::to_string(gold));
            waveText.setString("Wave: " + std::to_string(wave));

            for (auto& tower : towers)
                tower.update(dt, enemies);


            
        }

        window.clear();

        if (gameState == GameState::Menu)
        {
            window.clear(sf::Color(30, 30, 30));

            window.draw(titleText);
            window.draw(startButton);
            window.draw(startText);

            window.display();
            continue;
        }

        grid.draw(window);
        for (auto& enemy : enemies)
            if (!enemy.isDead())
                enemy.draw(window);

        for (auto& tower : towers)
            
            tower.draw(window);

        for (int i = 0; i < towers.size(); )
        {
            if (towers[i].isDestroyed())
            {
                if (selectedTowerIndex == i)
                    selectedTowerIndex = -1;

                towers.erase(towers.begin() + i);
            }
            else
            {
                i++;
            }
        }
        if (selectedTowerIndex != -1)
        {
            sf::CircleShape rangeCircle;
            float range = towers[selectedTowerIndex].getRange();

            rangeCircle.setRadius(range);
            rangeCircle.setOrigin({ range, range });
            rangeCircle.setPosition(towers[selectedTowerIndex].getPosition());
            rangeCircle.setFillColor(sf::Color(0, 255, 0, 50));

            window.draw(rangeCircle);

            Tower& t = towers[selectedTowerIndex];

            sf::Text towerInfo(font);
            towerInfo.setCharacterSize(20);


            upgradeText.setString("Upgrade");
            upgradeCostText.setString("Cost: " +
                std::to_string(t.getUpgradeCost()));

            
            sf::FloatRect textBounds = upgradeText.getLocalBounds();
            upgradeText.setOrigin({ textBounds.size.x / 2.f, textBounds.size.y / 2.f });
            upgradeText.setPosition({
                upgradeButton.getPosition().x + upgradeButton.getSize().x / 2.f,
                upgradeButton.getPosition().y + 7.f
                });

            
            sf::FloatRect costBounds = upgradeCostText.getLocalBounds();
            upgradeCostText.setOrigin({ costBounds.size.x / 2.f, costBounds.size.y / 2.f});
            float x = upgradeButton.getPosition().x + upgradeButton.getSize().x / 2.f;
            float y = upgradeButton.getPosition().y + 25.f;

            upgradeCostText.setPosition({
                std::floor(x),
                std::floor(y)
                });
            

            std::string typeName;

            switch (t.getType())
            {
            case Tower::TowerType::Basic: typeName = "Basic"; break;
            case Tower::TowerType::Sniper: typeName = "Sniper"; break;
            case Tower::TowerType::Rapid:  typeName = "Rapid"; break;
            }
            std::string info =
                "Tower Info\n"
                "Type: " + typeName + "\n" +
                "Level: " + std::to_string(t.getLevel()) + "\n" +
                "Damage: " + std::to_string((int)t.getDamage()) + "\n" +
                "Range: " + std::to_string((int)t.getRange()) + "\n";

            if (t.isNuclear())
                info += "Press F to Nuke!\n";
            else
                info += "Press F to Sacrifice\n";

            sf::RectangleShape panel({ 250.f, 220.f });
            panel.setFillColor(sf::Color(0, 0, 0, 150));
            panel.setPosition({ 990.f, 90.f });



     
            towerInfo.setCharacterSize(20);
            towerInfo.setString(info);
            towerInfo.setPosition({ window.getSize().x - 250.f, 100.f });

            window.draw(panel);
            window.draw(towerInfo);
            if (towers[selectedTowerIndex].getLevel() < 10)
                window.draw(upgradeButton);
                window.draw(upgradeText);
                window.draw(upgradeCostText);

            if (t.getLevel() >= 6 && t.getLevel() <= 9)
                info += "⚠ Unstable\n";
        }
            
        

        if (currentBuildMode != BuildMode::None)
        {
            window.draw(previewShape);
        }

        window.draw(hpText);
        window.draw(goldText);
        window.draw(scoreText);
        window.draw(waveText);
        window.draw(basicText);
        window.draw(sniperText);
        window.draw(rapidText);


        if (gameState == GameState::GameOver)
        {
            
            sf::Text gameOverText(font);
            gameOverText.setCharacterSize(60);
            gameOverText.setString("GAME OVER");
            gameOverText.setPosition({ 350.f, 250.f });

            window.draw(gameOverText);

            std::vector<int> topScores = loadScores();

            sf::Text leaderboard(font);
            leaderboard.setCharacterSize(30);

            std::string lb = "Top Scores:\n";
            for (int i = 0; i < topScores.size(); i++)
            {
                lb += std::to_string(i + 1) + ". " + std::to_string(topScores[i]) + "\n";
            }

            leaderboard.setString(lb);
            leaderboard.setPosition({ 350.f, 350.f });

            window.draw(leaderboard);

            sf::Text restartText(font);
            restartText.setCharacterSize(20);
            restartText.setString("Press R to Restart");
            restartText.setPosition({ 350.f, 570.f });

            window.draw(restartText);
        }

        window.display();
    }

    return 0;
}

