#include "Enemy.h"

// Base Enemy
Enemy::Enemy(int r, int h, int s) {
    row = r;
    col = 0;
    hp = h;
    speed = s;
}

void Enemy::move() {
    col += speed;
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
