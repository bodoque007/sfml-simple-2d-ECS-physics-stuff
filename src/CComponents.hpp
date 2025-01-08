#pragma once
#include <SFML/Graphics.hpp>

class CTransform 
{
    public:
        sf::Vector2f position = {0.0, 0.0};
        sf::Vector2f velocity = {0.0, 0.0};
        sf::Angle angle = sf::degrees(0.0f);

        CTransform(const sf::Vector2f& pos, const sf::Vector2f& vel) : 
            position(pos), velocity(vel) {}
};

class CShape 
{
    public:
        sf::CircleShape circle;

        CShape(float radius, int points, const sf::Color& fill, const sf::Color& outline, float thickness) :
            circle(radius, points)
        {
            circle.setFillColor(fill);
            circle.setOutlineColor(outline);
            circle.setOutlineThickness(thickness);
        }
};


class CCollision 
{
    public:
        float radius = 0;
        CCollision(float r) : radius(r) {};
};

class CScore 
{
    public:
        int score = 0;
        CScore(int s) : score(s) {};
};

class CLifespan 
{
    public:
        int remaining = 0;
        CLifespan(int life) : remaining(life) {};
};

class CInput 
{
    public:
        bool up = false;
        bool down = false;
        bool left = false;
        bool right = false;
        bool shoot = false;
        CInput() {};
};