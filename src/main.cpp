#include <SFML/Graphics.hpp>

#include <iostream>
#include <cmath>

const unsigned int HEIGHT = 1920u;
const unsigned int WIDTH = 1080u;
const float playerSpeed = 300.f;

int main() {
  auto window = sf::RenderWindow(sf::VideoMode({
    HEIGHT,
    WIDTH
  }), "CMake SFML Project");
  window.setFramerateLimit(144);

  sf::ConvexShape player;
  player.setPointCount(3); // Triangle
  player.setPoint(0, sf::Vector2f(0.f, 0.f));
  player.setPoint(1, sf::Vector2f(-25.f, 50.f));
  player.setPoint(2, sf::Vector2f(25.f, 50.f));
  player.setFillColor(sf::Color::Green);


  player.setPosition({
    HEIGHT / 2,
    WIDTH / 2
  });

  sf::Clock clock;

  int count = 1;
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
    std::cout << angle * 180 / 3.14159265 << std::endl;
    sf::Angle angle2 = sf::degrees(angle * 180 / 3.14159265 + 90.f);

    player.setRotation(angle2);

    window.clear();
    window.draw(player);
    window.display();
  }
}