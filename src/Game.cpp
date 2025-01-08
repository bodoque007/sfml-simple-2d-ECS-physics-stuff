#include "Game.hpp"
#include <iostream>

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
            if (m_elapsed.asMilliseconds() - m_lastEnemySpawn > 1000)
            {
                spawnEnemy();
                m_lastEnemySpawn = m_elapsed.asMilliseconds();
            }
            sMovement();
            sUserInput();
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

void Game::sMovement()
{
    m_player->transform->velocity = {0, 0};
    if (m_player->input->up) {
        m_player->transform->velocity.y -= 5;
    }
    if (m_player->input->down) {
        m_player->transform->velocity.y += 5;
    }
    if (m_player->input->left) {
        m_player->transform->velocity.x -= 5;
    }
    if (m_player->input->right) {
        m_player->transform->velocity.x += 5;
    }
    m_player->transform->position += m_player->transform->velocity;

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

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
        m_player->input->shoot = true;
    else
        m_player->input->shoot = false;
}