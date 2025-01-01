#ifndef ENEMY_HPP
#define ENEMY_HPP

#include <SFML/Graphics.hpp>

class Enemy {
public:
    sf::RectangleShape shape;
    sf::Vector2f direction;
    float speed;
    float shootCooldown;
    float shootTimer = 0.f;

    Enemy(sf::Vector2f position, sf::Vector2f dir, float spd, float shootCd);
    void update(float deltaTime);
    void resetShootTimer();
    bool canShoot();
};

#endif