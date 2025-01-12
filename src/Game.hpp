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
        bool isShooting = false;


        void init();
        void setPause(bool pause);

        void sMovement(const sf::Time& dt);
        void sUserInput();
        void sCollision();
        void sRender();
        void sEnemySpawner();
        void sLifeSpan(const sf::Time& dt);

        void spawnPlayer();
        void spawnEnemy();
        void spawnBullet(std::shared_ptr<Entity> entity, const sf::Vector2i& mousePos);

    public:
        Game();
        void run();
};