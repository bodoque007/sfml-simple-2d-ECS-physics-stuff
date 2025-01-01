#include "bullet.hpp"

Bullet::Bullet(sf::Vector2f position, sf::Vector2f dir, float spd) 
    : direction(dir), speed(spd) {
    shape.setSize(sf::Vector2f(10.f, 10.f));
    shape.setFillColor(sf::Color::Red);
    shape.setPosition(position);
}

void Bullet::update(float deltaTime) {
    shape.move(direction * speed * deltaTime);
}