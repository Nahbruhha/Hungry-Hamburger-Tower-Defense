#include "Map.h"
#include <vector>
#include <utility>
#include <iostream>


Map::Map() {
    rows = 30;
    cols = 30;
    
    // ล้างกระดาน
  for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            grid[i][j] = 0;

    int topLane = rows / 4;        // 30/4 = 7
    int middleRow = rows / 2;      // 15
    int bottomLane = rows - 5;     // 25
    int rightCol = cols - 6;       // 24

    //top_lane
        for (int j = 0; j < rightCol; j++) {
        grid[topLane][j] = 1;
        path.push_back({topLane, j});
        }

    //ทางลง
       for (int i = topLane; i < middleRow; i++) {
        grid[i][rightCol] = 1;
        path.push_back({i, rightCol});
       }

    //กลับมาทางซ้าย
        for (int j = rightCol; j >= 5; j--) {
        grid[middleRow][j] = 1;
        path.push_back({middleRow, j});
        }

    //ลงอีกนิด
      for (int i = middleRow; i < bottomLane; i++) {
        grid[i][5] = 1;
        path.push_back({i, 5});
      }

    //ทางตรงเข้าฐานและ
    for (int j = 5; j < cols - 1; j++) {
    grid[bottomLane][j] = 1;
    path.push_back({bottomLane, j});
}
    //ฐาน
    grid[bottomLane][cols - 1] = 2;
    path.push_back({bottomLane, cols - 1});


}
void Map::draw() {
    std::cout << "--- Hungry Hamburger Tower Defense Map ---" << std::endl;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            
            if (grid[i][j] == 0) {
                std::cout << ". "; //ที่ว่าง
            } 
            else if (grid[i][j] == 1) {
                std::cout << "# "; //ทางเดิน
            } 
            else if (grid[i][j] == 2) {
                std::cout << "H "; // ถ้าเป็นเลข 2 ให้พิมพ์ตัว H (ฐาน)
            }

        }
        std::cout << std::endl;
    }
}

bool Map::isPath(int r, int c) { 
    if (r < 0 || r >= rows || c < 0 || c >= cols) return false;
    return grid[r][c] == 1; 
}

bool Map::canPlace(int r, int c) { 
    if (r < 0 || r >= rows || c < 0 || c >= cols) return false;
    return grid[r][c] == 0; 
}

bool Map::reachedBase(int r, int c) { 
    if (r < 0 || r >= rows || c < 0 || c >= cols) 
        return false;

    return grid[r][c] == 2;
}
std::vector<std::pair<int,int>> Map::getPath() {
    return path;
}