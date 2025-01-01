#include <SFML/Graphics.hpp>

#include <iostream>
#include <cmath>
#include <algorithm>
#include "bullet.hpp"
#include "enemy.hpp"

const unsigned int HEIGHT = 1920u;
const unsigned int WIDTH = 1080u;
const float playerSpeed = 300.f;


void clearBullets(std::vector<Bullet>& bullets) {
  bullets.erase(std::remove_if(bullets.begin(), bullets.end(), [](const Bullet& bullet) {
    return bullet.shape.getPosition().x < 0 || bullet.shape.getPosition().x > HEIGHT || bullet.shape.getPosition().y < 0 || bullet.shape.getPosition().y > WIDTH;
  }), bullets.end());
}

int main() {
  auto window = sf::RenderWindow(sf::VideoMode({
    HEIGHT,
    WIDTH
  }), "Coldline Hawaii", sf::Style::Close | sf::Style::Titlebar);
  window.setFramerateLimit(144);

  sf::ConvexShape player;
  player.setPointCount(3);
  player.setPoint(0, sf::Vector2f(0.f, 0.f));
  player.setPoint(1, sf::Vector2f(-25.f, 50.f));
  player.setPoint(2, sf::Vector2f(25.f, 50.f));
  player.setFillColor(sf::Color::Green);

  Enemy enemy({HEIGHT / 2 - (HEIGHT / 3), WIDTH / 2}, {0.f, 100.f}, playerSpeed, 1.f);


  player.setPosition({
    HEIGHT / 2,
    WIDTH / 2
  });

  sf::Clock clock;

  int count = 1;
  std::vector<Bullet> bullets;
  bool isShooting = false;
  sf::Clock enemyShootClock;

  while (window.isOpen()) {
    float deltaTime = clock.restart().asSeconds();

    while (const std::optional event = window.pollEvent()) {
      if (event -> is < sf::Event::Closed > ()) {
        // debugging output
        std::cout << "Window closed" << std::endl;
        window.close();
      }
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
      player.move({-playerSpeed * deltaTime, 0.f});
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
      player.move({playerSpeed * deltaTime, 0.f});
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
      player.move({0.f, -playerSpeed * deltaTime});
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
      player.move({0.f, playerSpeed * deltaTime});
    }

    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
    sf::Vector2f playerPosition = player.getPosition();
    sf::Vector2f direction = {
      static_cast < float > (mousePosition.x) - playerPosition.x,
      static_cast < float > (mousePosition.y) - playerPosition.y
    };

    float angle = std::atan2(direction.y, direction.x);
    //std::cout << angle * 180 / 3.14159265 << std::endl;
    sf::Angle angle2 = sf::degrees(angle * 180 / 3.14159265 + 90.f);

    player.setRotation(angle2);

    sf::Vector2f directionBullet = {
      std::cos(angle),
      std::sin(angle)
    };

    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
      if (!isShooting) {
        bullets.emplace_back(Bullet(player.getPosition(), directionBullet, playerSpeed * 7.f));
        isShooting = true;
      }
    } else {
      isShooting = false;
    }

    for (auto& bullet : bullets) {
      bullet.update(deltaTime);
    }
    enemy.update(deltaTime);
    
    window.clear();
    window.draw(player);
    window.draw(enemy.shape);

    for (auto& bullet : bullets) {
      window.draw(bullet.shape);
    }
    clearBullets(bullets);

    if (enemyShootClock.getElapsedTime().asSeconds() >= 1.0f) {
        sf::Vector2f directionToPlayer = {
            player.getPosition().x - enemy.shape.getPosition().x,
            player.getPosition().y - enemy.shape.getPosition().y
        };

        // Normalize direction
        float magnitude = std::sqrt(directionToPlayer.x * directionToPlayer.x +
                                    directionToPlayer.y * directionToPlayer.y);
        directionToPlayer.x /= magnitude;
        directionToPlayer.y /= magnitude;

        bullets.emplace_back(Bullet(enemy.shape.getPosition(), directionToPlayer, playerSpeed * 5.f));
        enemyShootClock.restart();
    }
    
    window.display();
  }
}