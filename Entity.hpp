#include <iostream>
#include <SFML/Graphics.hpp>

struct Enemy {
    sf::RectangleShape shape;
    float health = 100.f;
    float speed = 100.f;
    bool isDead = false;

    Enemy(float x, float y) {
        shape.setSize({ 30.f, 30.f });
        shape.setFillColor(sf::Color::Green);
        shape.setOrigin({ 15.f, 15.f });
        shape.setPosition({ x, y });
    }

    void takeDamage(float amount) {
        health -= amount;
        if (health <= 0) isDead = true;
    }

    void update(float dt) {
        shape.move({ speed * dt, 0.f });
        // If they go off-screen, mark them as dead so we don't lag
        if (shape.getPosition().x > 2000) isDead = true;
    }
};