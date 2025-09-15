#pragma once
#include <glm/glm.hpp>
#include <memory>
#include <functional>

namespace Crumb
{
    class GameObject;
    class Collider;

    enum class ColliderType
    {
        AABB,
        Circle,
        Polygon
    };

    struct CollisionInfo
    {
        Collider *other;
        GameObject *otherGameObject;
        glm::vec2 point;
        glm::vec2 normal;
        float penetration;
    };

    class Collider
    {
    public:
        GameObject *m_gameObject;
        Collider(GameObject *gameObject, bool isTrigger = false);
        virtual ~Collider() = default;

        virtual ColliderType getType() const = 0;
        virtual bool checkCollision(const Collider *other, CollisionInfo &info) const = 0;
        virtual void updateFromGameObject() = 0;

        bool isTrigger() const { return m_isTrigger; }
        void setTrigger(bool trigger) { m_isTrigger = trigger; }

        GameObject *getGameObject() const { return m_gameObject; }

        void setCollisionLayer(int layer) { m_collisionLayer = layer; }
        void setCollisionMask(int mask) { m_collisionMask = mask; }
        int getCollisionLayer() const { return m_collisionLayer; }
        int getCollisionMask() const { return m_collisionMask; }

        bool canCollideWith(const Collider *other) const;

    protected:
        bool m_isTrigger;
        int m_collisionLayer = 0;
        int m_collisionMask = -1;

        GameObject *getGameObjectPtr() const { return m_gameObject; }
    };

    class AABBCollider : public Collider
    {
    public:
        AABBCollider(GameObject *gameObject, const glm::vec2 &offset = glm::vec2(0.0f),
                     const glm::vec2 &size = glm::vec2(0.0f), bool isTrigger = false);

        ColliderType getType() const override { return ColliderType::AABB; }
        bool checkCollision(const Collider *other, CollisionInfo &info) const override;
        bool checkAABBvsCircle(const class CircleCollider *other, CollisionInfo &info) const;
        void updateFromGameObject() override;

        glm::vec2 getMin() const { return m_center - m_halfSize; }
        glm::vec2 getMax() const { return m_center + m_halfSize; }
        glm::vec2 getCenter() const { return m_center; }
        glm::vec2 getSize() const { return m_halfSize * 2.0f; }
        glm::vec2 getHalfSize() const { return m_halfSize; }

        void setOffset(const glm::vec2 &offset)
        {
            m_offset = offset;
            updateFromGameObject();
        }
        void setSize(const glm::vec2 &size)
        {
            m_halfSize = size * 0.5f;
            updateFromGameObject();
        }

    private:
        glm::vec2 m_offset;
        glm::vec2 m_halfSize;
        glm::vec2 m_center;

        bool checkAABBvsAABB(const AABBCollider *other, CollisionInfo &info) const;
    };

    class CircleCollider : public Collider
    {
    public:
        CircleCollider(GameObject *gameObject, const glm::vec2 &offset = glm::vec2(0.0f),
                       float radius = 0.0f, bool isTrigger = false);

        ColliderType getType() const override { return ColliderType::Circle; }
        bool checkCollision(const Collider *other, CollisionInfo &info) const override;
        void updateFromGameObject() override;

        glm::vec2 getCenter() const { return m_center; }
        float getRadius() const { return m_radius; }

        void setOffset(const glm::vec2 &offset)
        {
            m_offset = offset;
            updateFromGameObject();
        }
        void setRadius(float radius) { m_radius = radius; }

    private:
        glm::vec2 m_offset;
        float m_radius;
        glm::vec2 m_center;

        bool checkCirclevsCircle(const CircleCollider *other, CollisionInfo &info) const;
        bool checkCirclevsAABB(const AABBCollider *other, CollisionInfo &info) const;
    };
}