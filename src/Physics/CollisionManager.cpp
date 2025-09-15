#include "CollisionManager.h"
#include "../Scene/GameObject.h"
#include <algorithm>

namespace Crumb
{
    CollisionManager::CollisionManager()
    {
    }

    void CollisionManager::addCollider(std::shared_ptr<Collider> collider)
    {
        if (collider && std::find(m_colliders.begin(), m_colliders.end(), collider) == m_colliders.end())
        {
            m_colliders.push_back(collider);
        }
    }

    void CollisionManager::removeCollider(std::shared_ptr<Collider> collider)
    {
        auto it = std::find(m_colliders.begin(), m_colliders.end(), collider);
        if (it != m_colliders.end())
        {

            auto collisionIt = m_activeCollisions.begin();
            while (collisionIt != m_activeCollisions.end())
            {
                if (collisionIt->objectA == collider->getGameObject() ||
                    collisionIt->objectB == collider->getGameObject())
                {

                    if (m_globalExitCallback)
                    {
                        m_globalExitCallback(collisionIt->objectA, collisionIt->objectB);
                    }
                    collisionIt = m_activeCollisions.erase(collisionIt);
                }
                else
                {
                    ++collisionIt;
                }
            }

            m_colliders.erase(it);
        }
    }

    void CollisionManager::clearColliders()
    {
        m_colliders.clear();
        m_activeCollisions.clear();
    }

    void CollisionManager::update()
    {
        if (!m_enabled)
            return;

        std::vector<CollisionPair> currentCollisions;

        for (auto &collider : m_colliders)
        {
            collider->updateFromGameObject();
        }

        for (size_t i = 0; i < m_colliders.size(); ++i)
        {
            for (size_t j = i + 1; j < m_colliders.size(); ++j)
            {
                auto &colliderA = m_colliders[i];
                auto &colliderB = m_colliders[j];

                CollisionInfo info;
                if (checkCollision(colliderA.get(), colliderB.get(), info))
                {
                    currentCollisions.emplace_back(colliderA->getGameObject(), colliderB->getGameObject());
                }
            }
        }

        processCollisionEvents(currentCollisions);
    }

    bool CollisionManager::checkCollision(Collider *colliderA, Collider *colliderB, CollisionInfo &info)
    {
        if (!colliderA || !colliderB)
            return false;
        if (colliderA == colliderB)
            return false;

        return colliderA->checkCollision(colliderB, info);
    }

    std::vector<Collider *> CollisionManager::queryPoint(const glm::vec2 &point, int layerMask)
    {
        std::vector<Collider *> result;

        for (auto &collider : m_colliders)
        {

            if (layerMask != -1 && (layerMask & (1 << collider->getCollisionLayer())) == 0)
                continue;

            bool hit = false;
            switch (collider->getType())
            {
            case ColliderType::AABB:
            {
                auto aabb = static_cast<AABBCollider *>(collider.get());
                hit = isPointInAABB(point, aabb);
                break;
            }
            case ColliderType::Circle:
            {
                auto circle = static_cast<CircleCollider *>(collider.get());
                hit = isPointInCircle(point, circle);
                break;
            }
            }

            if (hit)
            {
                result.push_back(collider.get());
            }
        }

        return result;
    }

    std::vector<Collider *> CollisionManager::queryAABB(const glm::vec2 &center, const glm::vec2 &halfSize, int layerMask)
    {
        std::vector<Collider *> result;

        GameObject tempGameObject("temp", center - halfSize, halfSize * 2.0f);
        AABBCollider queryCollider(&tempGameObject, glm::vec2(0.0f), halfSize * 2.0f);
        queryCollider.updateFromGameObject();

        for (auto &collider : m_colliders)
        {

            if (layerMask != -1 && (layerMask & (1 << collider->getCollisionLayer())) == 0)
                continue;

            CollisionInfo info;
            if (queryCollider.checkCollision(collider.get(), info))
            {
                result.push_back(collider.get());
            }
        }

        return result;
    }

    std::vector<Collider *> CollisionManager::queryCircle(const glm::vec2 &center, float radius, int layerMask)
    {
        std::vector<Collider *> result;

        GameObject tempGameObject("temp", center, glm::vec2(radius * 2.0f));
        CircleCollider queryCollider(&tempGameObject, glm::vec2(0.0f), radius);
        queryCollider.updateFromGameObject();

        for (auto &collider : m_colliders)
        {

            if (layerMask != -1 && (layerMask & (1 << collider->getCollisionLayer())) == 0)
                continue;

            CollisionInfo info;
            if (queryCollider.checkCollision(collider.get(), info))
            {
                result.push_back(collider.get());
            }
        }

        return result;
    }

    void CollisionManager::processCollisionEvents(const std::vector<CollisionPair> &currentCollisions)
    {

        std::unordered_set<CollisionPair> currentSet(currentCollisions.begin(), currentCollisions.end());

        for (const auto &collision : currentCollisions)
        {
            if (m_activeCollisions.find(collision) == m_activeCollisions.end())
            {

                if (m_globalEnterCallback)
                {
                    m_globalEnterCallback(collision.objectA, collision.objectB);
                }
            }
        }

        for (auto it = m_activeCollisions.begin(); it != m_activeCollisions.end();)
        {
            if (currentSet.find(*it) == currentSet.end())
            {

                if (m_globalExitCallback)
                {
                    m_globalExitCallback(it->objectA, it->objectB);
                }
                it = m_activeCollisions.erase(it);
            }
            else
            {
                ++it;
            }
        }

        m_activeCollisions = currentSet;
    }

    bool CollisionManager::isPointInAABB(const glm::vec2 &point, const AABBCollider *aabb)
    {
        glm::vec2 min = aabb->getMin();
        glm::vec2 max = aabb->getMax();

        return point.x >= min.x && point.x <= max.x &&
               point.y >= min.y && point.y <= max.y;
    }

    bool CollisionManager::isPointInCircle(const glm::vec2 &point, const CircleCollider *circle)
    {
        glm::vec2 distance = point - circle->getCenter();
        float distanceSquared = distance.x * distance.x + distance.y * distance.y;
        float radiusSquared = circle->getRadius() * circle->getRadius();

        return distanceSquared <= radiusSquared;
    }
}