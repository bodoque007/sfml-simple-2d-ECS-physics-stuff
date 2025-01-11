#include "EntityManager.hpp"
#include <algorithm>
#include <iostream>

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
    m_entities.erase(
        std::remove_if(m_entities.begin(), m_entities.end(),
            [](const auto& entity) { return !entity->isActive(); }
        ),
        m_entities.end()
    );

    for (auto& [tag, entities] : m_entities_by_tag) {
        entities.erase(
            std::remove_if(entities.begin(), entities.end(),
                [](const auto& entity) { 
                    return !entity || !entity->isActive(); 
                }
            ),
            entities.end()
        );
    }

    for (auto& entity : m_entities_to_add)
    {
        m_entities.push_back(entity);
        m_entities_by_tag[entity->getTag()].push_back(entity);
    }

    m_entities_to_add.clear();
}

std::vector<std::shared_ptr<Entity>> EntityManager::getEntities()
{
    return m_entities;
}


std::vector<std::shared_ptr<Entity>> EntityManager::getEntitiesByTag(const std::string& tag)
{
    return m_entities_by_tag[tag];
}