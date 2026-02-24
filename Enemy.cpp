#include "Enemy.h"

// Base Enemy
Enemy::Enemy(int r, int h, int s) {
    row = r;
    col = 0;
    hp = h;
    speed = s;
    pathIndex = 0;
}

void Enemy::move(const std::vector<std::pair<int,int>>& path) {

    pathIndex += speed;

    if (pathIndex >= path.size())
        pathIndex = path.size() - 1;

    row = path[pathIndex].first;
    col = path[pathIndex].second;
}

void Enemy::takeDamage(int dmg) {
    hp -= dmg;
}

bool Enemy::isDead() {
    return hp <= 0;
}

int Enemy::getRow() { return row; }
int Enemy::getCol() { return col; }
int Enemy::getHP() { return hp; }


// Normal Enemy
NormalEnemy::NormalEnemy(int r)
    : Enemy(r, 100, 1)  // HP 100 speed 1
{
}


// Fast Enemy
FastEnemy::FastEnemy(int r)
    : Enemy(r, 70, 2)   // HP 70 speed 2
{
}
