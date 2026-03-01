#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class Grid
{
public:
    enum class TileType
    {
        Empty,
        Path,
        Tower
    };

    Grid(int rows, int cols, int tileSize);

    void draw(sf::RenderWindow& window) const;

    sf::Vector2i getCellFromPixel(const sf::Vector2i& mousePos) const;
    bool isValidCell(int row, int col) const;
    
    TileType getTile(int row, int col) const;
    void setTile(int row, int col, TileType type);

    void createFixedPath();
    const std::vector<sf::Vector2f>& getPath() const;

private:
    int m_rows;
    int m_cols;
    int m_tileSize;

    std::vector<std::vector<TileType>> m_grid;
    std::vector<sf::Vector2f> m_pathPoints;
   
};