#ifndef MAP_H
#define MAP_H

class Map {
private:
    int rows;
    int cols;
    int grid[10][10]; // 0 = หญ้า (วางป้อมได้), 1 = ทางเดิน (ศัตรูเดิน), 2 = ฐาน (Hamburger)

public:
    Map();           // Constructor: สร้างแมพเริ่มต้น
    void draw();     // Function: วาดแมพออกมาดูในหน้าจอ Console
    bool isPath(int r, int c);  // Function: เช็กว่าเป็นทางเดินไหม
    bool canPlace(int r, int c); // Function: เช็กว่าว่างพอจะวางป้อมไหม
};

#endif