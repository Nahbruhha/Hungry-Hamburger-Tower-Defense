#ifndef MAP_H
#define MAP_H

class Map {
private:
    int rows;
    int cols;
    int grid[30][30];

public:
    Map();
    void draw();
    bool isPath(int r, int c);
    bool canPlace(int r, int c);
    bool reachedBase(int r, int c); 
};

#endif