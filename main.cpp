#include <iostream>
#include "Map.h"

int main() {
    Map myMap;      // สร้างวัตถุแผนที่
    myMap.draw();   // สั่งวาดแผนที่
    
    // ลองทดสอบฟังก์ชัน canPlace
    if(myMap.canPlace(0, 0)) {
        std::cout << "You can place a tower at (0,0)" << std::endl;
    }
    
    return 0;
}