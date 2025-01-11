#pragma once

#include "CComponents.hpp"
#include <memory>
#include <string>

class Entity 
{
    friend class EntityManager;

    bool m_active = true;
    size_t m_id = 0;
    std::string m_tag = "default";

    public:
        Entity(const size_t id, const std::string& tag) : m_id(id), m_tag(tag) {};
        std::shared_ptr<CTransform> transform;
        std::shared_ptr<CShape> shape;
        std::shared_ptr<CCollision> collision;
        std::shared_ptr<CInput> input;
        std::shared_ptr<CScore> score;
        std::shared_ptr<CLifespan> lifespan;

        const size_t getId() const;
        const std::string& getTag() const;
        void destroy();
        bool isActive();
};