#include "enemy.hpp"
const unsigned int WIDTH = 1080u;

Enemy::Enemy(sf::Vector2f position, sf::Vector2f dir, float spd, float shootCd) 
    : direction(dir), speed(spd) {
    shape.setSize(sf::Vector2f(50.f, 50.f));
    shape.setFillColor(sf::Color::Red);
    shape.setPosition(position);
}

void Enemy::update(float deltaTime) {
    sf::Vector2f pos = shape.getPosition();
    if (pos.y <= 0 || pos.y >= WIDTH - shape.getSize().y) {
        speed = -speed;
    }
    shape.move({0.f, speed * deltaTime});
    shootTimer += deltaTime;
}

bool Enemy::canShoot() {
    return shootTimer >= shootCooldown;
}

void Enemy::resetShootTimer() {
    shootTimer = 0.0f;
}