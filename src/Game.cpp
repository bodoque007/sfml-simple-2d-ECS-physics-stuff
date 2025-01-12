#include "Game.hpp"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>

Game::Game() : m_window(sf::VideoMode({1000, 800}), "ECS Asteroids")
{
    m_window.setFramerateLimit(60);
    m_window.setVerticalSyncEnabled(true);
    m_entityManager = std::make_shared<EntityManager>();
}

void Game::init()
{
    m_score = 0;
    m_lastEnemySpawn = 0;
    m_running = true;
    std::srand(static_cast<unsigned>(std::time(nullptr)));
    spawnPlayer();
}

void Game::run()
{
    init();

    while (m_window.isOpen())
    {
        sf::Time dt = m_clock.restart();
        m_elapsed += dt;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::P))
        {
            m_running = !m_running;
        }

        while (const std::optional event = m_window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                m_window.close();
            }
        }
        if (m_running)
        {
            sUserInput();
            sCollision();
            if (m_elapsed.asMilliseconds() - m_lastEnemySpawn > 1000)
            {
                spawnEnemy();
                m_lastEnemySpawn = m_elapsed.asMilliseconds();
            }
            sMovement(dt);
            sLifeSpan(dt);
        }
        sRender();
    }
}

void Game::setPause(bool pause)
{
    m_running = !pause;
}

void Game::spawnPlayer()
{
    auto player = m_entityManager->addEntity("player");

    player->transform = std::make_shared<CTransform>(sf::Vector2f(200.0f, 200.0f), sf::Vector2f(1.0f, 1.0f));
    player->shape = std::make_shared<CShape>(10.0f, 3, sf::Color::Green, sf::Color::White, 1.0f);
    player->collision = std::make_shared<CCollision>(10.0f);
    player->input = std::make_shared<CInput>();

    m_player = player;
}

void Game::sRender()
{
    m_window.clear();
    m_entityManager->update();

    for (auto& entity : m_entityManager->getEntities())
    {
        entity->transform->angle += sf::degrees(1.0f);
        entity->shape->circle.setRotation(entity->transform->angle);

        entity->shape->circle.setPosition(entity->transform->position);
        m_window.draw(entity->shape->circle);
    }

    m_window.display();
}

void Game::sMovement(const sf::Time& dt)
{
    float dt_seconds = dt.asSeconds();
    m_player->transform->velocity = {0, 0};
    if (m_player->input->up) {
        m_player->transform->velocity.y -= 300.f;
    }
    if (m_player->input->down) {
        m_player->transform->velocity.y += 300.f;
    }
    if (m_player->input->left) {
        m_player->transform->velocity.x -= 300.f;
    }
    if (m_player->input->right) {
        m_player->transform->velocity.x += 300.f;
    }
    

    for (auto& entity : m_entityManager->getEntities())
    {
        entity->transform->position += entity->transform->velocity * dt_seconds;
        if (entity->transform->position.x > m_window.getSize().x 
        || entity->transform->position.x < 0
        || entity->transform->position.y > m_window.getSize().y
        || entity->transform->position.y < 0)
        {
            entity->destroy();
        }
    }

}

void Game::sUserInput()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
        m_player->input->up = true;
    else
        m_player->input->up = false;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
        m_player->input->down = true;
    else
        m_player->input->down = false;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
        m_player->input->left = true;
    else
        m_player->input->left = false;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
        m_player->input->right = true;
    else
        m_player->input->right = false;
    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
        m_player->input->shoot = true;
    else
        m_player->input->shoot = false;

    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
      if (!isShooting) {
        spawnBullet(m_player, sf::Mouse::getPosition(m_window));
        isShooting = true;
      }
    } else {
      isShooting = false;
    }
}

void Game::spawnEnemy()
{
    auto enemy = m_entityManager->addEntity("enemy");

    float randomX = static_cast<float>(std::rand() % m_window.getSize().x);
    float randomY = static_cast<float>(std::rand() % m_window.getSize().y);
    sf::Vector2f randomPosition(randomX, randomY);

    float randomX_velocity = static_cast<float>(std::rand() % 3);
    float randomY_velocity = static_cast<float>(std::rand() % 3);
    int randomSign = (std::rand() % 2) * 2 - 1;
    
    sf::Vector2f randomVelocity(randomX_velocity * randomSign, randomY_velocity * randomSign);

    int randomPolygons = 3 + (std::rand() % 10);

    enemy->transform = std::make_shared<CTransform>(randomPosition, randomVelocity + sf::Vector2f(1.0f * randomSign, 1.0f * randomSign) * 300.f);
    enemy->shape = std::make_shared<CShape>(10.0f, randomPolygons, sf::Color::Red, sf::Color::White, 1.0f);
    enemy->collision = std::make_shared<CCollision>(10.0f);
    enemy->lifespan = std::make_shared<CLifespan>(2.f);

    enemy->shape->circle.setOrigin({enemy->shape->circle.getRadius(), enemy->shape->circle.getRadius()});
}

void Game::spawnBullet(std::shared_ptr<Entity> entity, const sf::Vector2i& mousePos)
{
    auto bullet = m_entityManager->addEntity("bullet");
    sf::Vector2f playerPosition = entity->transform->position;

    sf::Vector2f direction = {
      static_cast < float > (mousePos.x) - playerPosition.x,
      static_cast < float > (mousePos.y) - playerPosition.y
    };
    
    float length = std::sqrt(direction.x*direction.x + direction.y*direction.y);

    sf::Vector2f directionNormalized = { direction.x / length, direction.y / length };

    bullet->shape = std::make_shared<CShape>(5.0f, 3, sf::Color::Blue, sf::Color::White, 1.0f);
    bullet->collision = std::make_shared<CCollision>(5.0f);
    bullet->shape->circle.setOrigin({bullet->shape->circle.getRadius(), bullet->shape->circle.getRadius()});
    bullet->transform = std::make_shared<CTransform>(playerPosition, sf::Vector2f(directionNormalized.x * 400.f, directionNormalized.y * 400.f));
}

void Game::sCollision()
{
    for (auto& bullet : m_entityManager->getEntitiesByTag("bullet"))
    {
        for (auto& enemy : m_entityManager->getEntitiesByTag("enemy"))
        {
            if (!enemy->collision) continue;
            float distanceSquared = std::pow(bullet->shape->circle.getPosition().x - enemy->shape->circle.getPosition().x, 2) +
                                    std::pow(bullet->shape->circle.getPosition().y - enemy->shape->circle.getPosition().y, 2);
            if (distanceSquared < std::pow(bullet->collision->radius + enemy->collision->radius, 2)) {
                bullet->destroy();
                enemy->destroy();
                float angle = 0;
                for (int i = 0; i < enemy->shape->circle.getPointCount(); i++)
                {
                    angle += (360 / enemy->shape->circle.getPointCount());
                    auto enemyPiece = m_entityManager->addEntity("enemy");
                    sf::Vector2f velocity(std::cos(angle), std::sin(angle));
                    enemyPiece->transform = std::make_shared<CTransform>(enemy->transform->position, velocity * 256.f);
                    enemyPiece->shape = std::make_shared<CShape>(3, enemy->shape->circle.getPointCount(), sf::Color::Blue, sf::Color::White, 1.0f);
                }
            }
        }
    }
}

void Game::sLifeSpan(const sf::Time& dt)
{
    for (auto& entity : m_entityManager->getEntitiesByTag("enemy"))
    {
        if (!entity->lifespan) continue;
        entity->lifespan->remaining -= dt.asSeconds();
        if (entity->lifespan->remaining <= 0) entity->destroy();
    }
}