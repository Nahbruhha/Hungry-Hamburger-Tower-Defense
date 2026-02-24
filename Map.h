#ifndef MAP_H
#define MAP_H
#include <vector>
#include <utility>

class Map {
private:
    int rows;
    int cols;
    int grid[30][30];
    std::vector<std::pair<int,int>> path;

public:
    Map();
    void draw();
    bool isPath(int r, int c);
    bool canPlace(int r, int c);
    bool reachedBase(int r, int c); 
    std::vector<std::pair<int,int>> getPath();
};

#endif