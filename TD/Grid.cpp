#include "Grid.h"

Grid::Grid(int rows, int cols, int tileSize)
    : m_rows(rows), m_cols(cols), m_tileSize(tileSize)
{
    m_grid.resize(m_rows, std::vector<TileType>(m_cols, TileType::Empty));
}

void Grid::draw(sf::RenderWindow& window) const
{
    sf::RectangleShape tileShape({
    static_cast<float>(m_tileSize),
    static_cast<float>(m_tileSize)
        });

    tileShape.setOutlineThickness(-1.f);
    tileShape.setOutlineColor(sf::Color(0, 0, 0, 40));



    for (int row = 0; row < m_rows; row++)
    {
        for (int col = 0; col < m_cols; col++)
        {
            tileShape.setPosition({
                static_cast<float>(col * m_tileSize),
                static_cast<float>(row * m_tileSize)
                });

            switch (m_grid[row][col])
            {
            case TileType::Empty:
                tileShape.setFillColor(sf::Color(50, 50, 50));
                break;

            case TileType::Path:
                tileShape.setFillColor(sf::Color::Yellow);
                break;

            case TileType::Tower:
                tileShape.setFillColor(sf::Color::Blue);
                break;
            }
            switch (m_grid[row][col])
            {
            case TileType::Empty:
                tileShape.setFillColor(sf::Color(34, 139, 34)); // grass green
                break;

            case TileType::Path:
                tileShape.setFillColor(sf::Color(139, 69, 19)); // dirt brown
                break;

            case TileType::Tower:
                tileShape.setFillColor(sf::Color(100, 100, 255)); // tower base
                break;
            }


            window.draw(tileShape);
        }
    }
}

sf::Vector2i Grid::getCellFromPixel(const sf::Vector2i& mousePos) const
{
    int col = mousePos.x / m_tileSize;
    int row = mousePos.y / m_tileSize;

    return { row, col };
}

bool Grid::isValidCell(int row, int col) const
{
    return row >= 0 && row < m_rows &&
        col >= 0 && col < m_cols;
}

Grid::TileType Grid::getTile(int row, int col) const
{
    return m_grid[row][col];
}

void Grid::setTile(int row, int col, TileType type)
{
    m_grid[row][col] = type;
}
 // สร้างแมพ
void Grid::createFixedPath()
{
    m_pathPoints.clear();
    
    for (int col = 0; col < 10; col++) {
        m_grid[3][col] = TileType::Path;
        sf::Vector2f worldPos(
            col * m_tileSize + m_tileSize / 2.f,
            3 * m_tileSize + m_tileSize / 2.f
        );

        m_pathPoints.push_back(worldPos);
    }
    
    for (int row = 3; row < 8; row++) {
        m_grid[row][10] = TileType::Path;
        sf::Vector2f worldPos(
            10 * m_tileSize + m_tileSize / 2.f,
            row * m_tileSize + m_tileSize / 2.f
        );

        m_pathPoints.push_back(worldPos);
    
    }
    
    for (int col = 9; col > 2; col--) {
        m_grid[7][col] = TileType::Path;
        sf::Vector2f worldPos(
            col * m_tileSize + m_tileSize / 2.f,
            7 * m_tileSize + m_tileSize / 2.f
        );

        m_pathPoints.push_back(worldPos);
    }
    
    for (int row = 7; row < 12; row++) {
        m_grid[row][2] = TileType::Path;
        sf::Vector2f worldPos(
            2 * m_tileSize + m_tileSize / 2.f,
            row * m_tileSize + m_tileSize / 2.f
        );

        m_pathPoints.push_back(worldPos);
    }

    for (int col = 2; col < 14; col++) {
        m_grid[11][col] = TileType::Path;
        sf::Vector2f worldPos(
            col * m_tileSize + m_tileSize / 2.f,
            11 * m_tileSize + m_tileSize / 2.f
        );

        m_pathPoints.push_back(worldPos);
    }
    
    for (int row = 11; row > 2; row--) {
        m_grid[row][14] = TileType::Path;
        sf::Vector2f worldPos(
            14 * m_tileSize + m_tileSize / 2.f,
            row * m_tileSize + m_tileSize / 2.f
        );

        m_pathPoints.push_back(worldPos);
    }

    for (int col = 14; col < 18; col++) {
        m_grid[2][col] = TileType::Path;
        sf::Vector2f worldPos(
            col * m_tileSize + m_tileSize / 2.f,
            2 * m_tileSize + m_tileSize / 2.f
        );

        m_pathPoints.push_back(worldPos);
    }

    for (int row = 2; row < 10; row++) {
        m_grid[row][17] = TileType::Path;
        sf::Vector2f worldPos(
            17 * m_tileSize + m_tileSize / 2.f,
            row * m_tileSize + m_tileSize / 2.f
        );

        m_pathPoints.push_back(worldPos);
    }

    for (int col = 17; col < 20; col++) {
        m_grid[9][col] = TileType::Path;
        sf::Vector2f worldPos(
            col * m_tileSize + m_tileSize / 2.f,
            9 * m_tileSize + m_tileSize / 2.f
        );

        m_pathPoints.push_back(worldPos);
    }

}

const std::vector<sf::Vector2f>& Grid::getPath() const
{
    return m_pathPoints;
}