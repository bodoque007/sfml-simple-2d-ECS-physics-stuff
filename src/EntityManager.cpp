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
    m_entities.push_back(std::shared_ptr<Entity>(new Entity(m_idCounter++, tag)));
    return m_entities.back();
}