#ifndef ENEMY_H
#define ENEMY_H

#include <string>
#include <vector>
#include <utility>

class Enemy {
protected:
    int row;
    int col;
    int hp;
    int speed;
    int pathIndex;

public:
    Enemy(int r, int h, int s);
    virtual ~Enemy() {}

    virtual void move(const std::vector<std::pair<int,int>>& path);
    void takeDamage(int dmg);
    bool isDead();

    int getRow();
    int getCol();
    int getHP();
};

class NormalEnemy : public Enemy {
public:
    NormalEnemy(int r);
};

class FastEnemy : public Enemy {
public:
    FastEnemy(int r);
};

#endif
