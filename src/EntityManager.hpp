#include <SFML/Graphics.hpp>
#include <memory>

#include "Entity.hpp"

class EntityManager
{
    public:
        EntityManager();
        ~EntityManager();
        void clear();
        void update(const sf::Time& dt);
        std::shared_ptr<Entity> addEntity(const std::string& tag);
        void destroyEntity(const size_t id);
        std::shared_ptr<Entity> getEntity(const size_t id);
        std::vector<std::shared_ptr<Entity>> getEntitiesByTag(const std::string& tag);
        std::vector<std::shared_ptr<Entity>> getEntities();
    private:
        std::vector<std::shared_ptr<Entity>> m_entities;
        size_t m_idCounter = 0;
};