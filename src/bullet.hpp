#ifndef BULLET_HPP
#define BULLET_HPP

#include <SFML/Graphics.hpp>

class Bullet {
public:
    sf::RectangleShape shape;
    sf::Vector2f direction;
    float speed;

    Bullet(sf::Vector2f position, sf::Vector2f dir, float spd);
    void update(float deltaTime);
};

#endif