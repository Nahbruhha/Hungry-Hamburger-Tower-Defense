#include <iostream>
#include "Map.h"

int main() {
    Map myMap;      // สร้างวัตถุแผนที่
    myMap.draw();   // สั่งวาดแผนที่
    
    // ===== ทดสอบฟังก์ชัน canPlace() =====
    // เช็คว่าวาง Tower ที่ตำแหน่ง (0,0) ได้ไหม
    if (myMap.canPlace(0, 0))
        std::cout << "You can place a tower at (0,0)\n";
    else
        std::cout << "Cannot place at (0,0)\n";

    // เช็คตำแหน่ง (3,0) ซึ่งเป็นทางเดิน ควรวางไม่ได้
    if (myMap.canPlace(3, 0))
        std::cout << "You can place at (3,0)\n";
    else
        std::cout << "Cannot place at (3,0) (This is path)\n";


    // ===== ทดสอบฟังก์ชัน isPath() =====
    // เช็คว่าตำแหน่ง (3,0) เป็นทางเดินหรือไม่
    if (myMap.isPath(3, 0))
        std::cout << "(3,0) is a path\n";

    // เช็คว่าตำแหน่ง (0,0) ไม่ใช่ทางเดิน
    if (!myMap.isPath(0, 0))
        std::cout << "(0,0) is NOT a path\n";


    // ===== ทดสอบฟังก์ชัน reachedBase() =====
    // เช็คว่าตำแหน่ง (4,9) คือฐานหรือไม่
    if (myMap.reachedBase(4, 9))
        std::cout << "(4,9) is the BASE (H)\n";

    // เช็คว่าตำแหน่งอื่นไม่ใช่ฐาน
    if (!myMap.reachedBase(3, 9))
        std::cout << "(3,9) is NOT the base\n";


    // ===== ทดสอบกรณีตำแหน่งเกินขอบเขต =====
    // ตำแหน่ง (100,100) อยู่นอกแผนที่ ต้อง return false
    if (!myMap.canPlace(100, 100))
        std::cout << "(100,100) is invalid position\n";


    return 0;
}