#include "SFML/Graphics.hpp"
#include <memory>
#include "Entity.hpp"
#include "EntityManager.hpp"

class Game
{
    private:
        sf::RenderWindow m_window;
        sf::Clock m_clock;
        sf::Time m_elapsed;
        bool m_running = false;
        int m_score = 0;
        int m_lastEnemySpawn = 0;
        std::shared_ptr<Entity> m_player;
        std::shared_ptr<EntityManager> m_entityManager;


        void init();
        void setPause(bool pause);

        void sMovement();
        void sUserInput();
        void sCollision();
        void sRender();
        void sEnemySpawner();
        void sLifeSpan();

        void spawnPlayer();
        void spawnEnemy();
        void spawnBullet(std::shared_ptr<Entity> entity, const sf::Vector2f& mousePos);

    public:
        Game();
        void run();
};