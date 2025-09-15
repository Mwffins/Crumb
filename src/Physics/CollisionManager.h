#pragma once
#include "Collider.h"
#include <vector>
#include <memory>
#include <unordered_set>
#include <functional>

namespace Crumb
{
    class Scene;

    using CollisionCallback = std::function<void(const CollisionInfo &)>;
    using CollisionEnterCallback = std::function<void(GameObject *, GameObject *)>;
    using CollisionExitCallback = std::function<void(GameObject *, GameObject *)>;

    struct CollisionPair
    {
        GameObject *objectA;
        GameObject *objectB;

        CollisionPair(GameObject *a, GameObject *b)
        {

            if (a < b)
            {
                objectA = a;
                objectB = b;
            }
            else
            {
                objectA = b;
                objectB = a;
            }
        }

        bool operator==(const CollisionPair &other) const
        {
            return objectA == other.objectA && objectB == other.objectB;
        }
    };
}

namespace std
{
    template <>
    struct hash<Crumb::CollisionPair>
    {
        size_t operator()(const Crumb::CollisionPair &pair) const
        {
            return hash<void *>()(pair.objectA) ^ (hash<void *>()(pair.objectB) << 1);
        }
    };
}

namespace Crumb
{
    class CollisionManager
    {
    public:
        CollisionManager();
        ~CollisionManager() = default;

        void addCollider(std::shared_ptr<Collider> collider);
        void removeCollider(std::shared_ptr<Collider> collider);
        void clearColliders();

        void update();

        bool checkCollision(Collider *colliderA, Collider *colliderB, CollisionInfo &info);
        std::vector<Collider *> queryPoint(const glm::vec2 &point, int layerMask = -1);
        std::vector<Collider *> queryAABB(const glm::vec2 &center, const glm::vec2 &halfSize, int layerMask = -1);
        std::vector<Collider *> queryCircle(const glm::vec2 &center, float radius, int layerMask = -1);

        void setGlobalCollisionEnterCallback(CollisionEnterCallback callback) { m_globalEnterCallback = callback; }
        void setGlobalCollisionExitCallback(CollisionExitCallback callback) { m_globalExitCallback = callback; }

        void setEnabled(bool enabled) { m_enabled = enabled; }
        bool isEnabled() const { return m_enabled; }

        size_t getColliderCount() const { return m_colliders.size(); }
        const std::vector<std::shared_ptr<Collider>> &getColliders() const { return m_colliders; }

    private:
        std::vector<std::shared_ptr<Collider>> m_colliders;
        std::unordered_set<CollisionPair> m_activeCollisions;

        CollisionEnterCallback m_globalEnterCallback;
        CollisionExitCallback m_globalExitCallback;

        bool m_enabled = true;

        void processCollisionEvents(const std::vector<CollisionPair> &currentCollisions);
        bool isPointInAABB(const glm::vec2 &point, const AABBCollider *aabb);
        bool isPointInCircle(const glm::vec2 &point, const CircleCollider *circle);
    };
}