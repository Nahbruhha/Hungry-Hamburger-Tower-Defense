#include "Map.h"
#include <iostream>


Map::Map() {
    rows = 10;
    cols = 10;
    
    // 1. ล้างกระดานให้เป็นหญ้า (0) ทั้งหมด
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            grid[i][j] = 0;
        }
    }

    // 2. สร้างทางเดินเป็นเส้นตรง (แถวที่ 5 ตั้งแต่คอลัมน์ 0 ถึง 8)
    int pathRow = 5; // กำหนดให้เดินที่แถวที่ 5
    for (int j = 0; j < 9; j++) {
        grid[pathRow][j] = 1; 
    }

    // 3. วางเป้าหมาย (H) ไว้ที่ปลายเส้นตรง (แถวที่ 5 คอลัมน์ที่ 9)
    grid[pathRow][9] = 2; 
}
void Map::draw() {
    std::cout << "--- Hungry Hamburger Tower Defense Map ---" << std::endl;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            
            if (grid[i][j] == 0) {
                std::cout << ". "; // พื้นที่ว่าง
            } 
            else if (grid[i][j] == 1) {
                std::cout << "# "; // ทางเดินศัตรู
            } 
            else if (grid[i][j] == 2) {
                std::cout << "H "; // นี่คือส่วนที่เพิ่มเข้ามา: ถ้าเป็นเลข 2 ให้พิมพ์ตัว H
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