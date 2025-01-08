#include "EntityManager.hpp"


EntityManager::EntityManager()
{
}

EntityManager::~EntityManager()
{
    clear();
}

void EntityManager::clear()
{
    m_entities.clear();
}

std::shared_ptr<Entity> EntityManager::addEntity(const std::string& tag)
{
    auto entity = std::shared_ptr<Entity>(new Entity(m_idCounter++, tag));
    m_entities_to_add.push_back(entity);
    return entity;
}

void EntityManager::update()
{
    for (auto& entity : m_entities_to_add)
    {
        m_entities.push_back(entity);
    }
    m_entities_to_add.clear();
    m_entities_to_destroy.clear();
}

std::vector<std::shared_ptr<Entity>> EntityManager::getEntities()
{
    return m_entities;
}