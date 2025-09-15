#include "Collider.h"
#include "../Scene/GameObject.h"
#include <algorithm>
#include <cmath>

namespace Crumb
{

    Collider::Collider(GameObject *gameObject, bool isTrigger)
        : m_gameObject(gameObject), m_isTrigger(isTrigger)
    {
    }

    bool Collider::canCollideWith(const Collider *other) const
    {
        if (!other)
            return false;

        return (m_collisionMask & (1 << other->m_collisionLayer)) != 0;
    }

    AABBCollider::AABBCollider(GameObject *gameObject, const glm::vec2 &offset,
                               const glm::vec2 &size, bool isTrigger)
        : Collider(gameObject, isTrigger), m_offset(offset), m_halfSize(size * 0.5f)
    {
        updateFromGameObject();
    }

    void AABBCollider::updateFromGameObject()
    {
        if (m_gameObject)
        {
            m_center = m_gameObject->getPosition() + m_offset;

            if (m_halfSize.x == 0.0f && m_halfSize.y == 0.0f)
            {
                m_halfSize = m_gameObject->getSize() * 0.5f;
                m_center += m_halfSize;
            }
        }
    }

    bool AABBCollider::checkCollision(const Collider *other, CollisionInfo &info) const
    {
        if (!canCollideWith(other))
            return false;

        switch (other->getType())
        {
        case ColliderType::AABB:
            return checkAABBvsAABB(static_cast<const AABBCollider *>(other), info);
        case ColliderType::Circle:
            return checkAABBvsCircle(static_cast<const CircleCollider *>(other), info);
        default:
            return false;
        }
    }

    bool AABBCollider::checkAABBvsAABB(const AABBCollider *other, CollisionInfo &info) const
    {
        glm::vec2 distance = other->m_center - m_center;
        glm::vec2 minDistance = m_halfSize + other->m_halfSize;

        if (std::abs(distance.x) < minDistance.x && std::abs(distance.y) < minDistance.y)
        {

            info.other = const_cast<AABBCollider *>(other);
            info.otherGameObject = other->m_gameObject;

            float xOverlap = minDistance.x - std::abs(distance.x);
            float yOverlap = minDistance.y - std::abs(distance.y);

            if (xOverlap < yOverlap)
            {

                info.normal = glm::vec2(distance.x > 0 ? -1.0f : 1.0f, 0.0f);
                info.penetration = xOverlap;
                info.point = glm::vec2(
                    distance.x > 0 ? m_center.x + m_halfSize.x : m_center.x - m_halfSize.x,
                    m_center.y);
            }
            else
            {

                info.normal = glm::vec2(0.0f, distance.y > 0 ? -1.0f : 1.0f);
                info.penetration = yOverlap;
                info.point = glm::vec2(
                    m_center.x,
                    distance.y > 0 ? m_center.y + m_halfSize.y : m_center.y - m_halfSize.y);
            }

            return true;
        }

        return false;
    }

    bool AABBCollider::checkAABBvsCircle(const CircleCollider *other, CollisionInfo &info) const
    {
        glm::vec2 distance = other->getCenter() - m_center;

        glm::vec2 closest = glm::clamp(other->getCenter(), getMin(), getMax());
        glm::vec2 difference = other->getCenter() - closest;

        float distanceSquared = difference.x * difference.x + difference.y * difference.y;
        float radiusSquared = other->getRadius() * other->getRadius();

        if (distanceSquared <= radiusSquared)
        {
            info.other = const_cast<CircleCollider *>(other);
            info.otherGameObject = other->m_gameObject;

            float distance = std::sqrt(distanceSquared);
            if (distance > 0.0f)
            {
                info.normal = difference / distance;
                info.penetration = other->getRadius() - distance;
                info.point = closest;
            }
            else
            {

                info.normal = glm::vec2(1.0f, 0.0f);
                info.penetration = other->getRadius();
                info.point = other->getCenter();
            }

            return true;
        }

        return false;
    }

    CircleCollider::CircleCollider(GameObject *gameObject, const glm::vec2 &offset,
                                   float radius, bool isTrigger)
        : Collider(gameObject, isTrigger), m_offset(offset), m_radius(radius)
    {
        updateFromGameObject();
    }

    void CircleCollider::updateFromGameObject()
    {
        if (m_gameObject)
        {
            m_center = m_gameObject->getPosition() + m_offset;

            if (m_radius == 0.0f)
            {
                glm::vec2 size = m_gameObject->getSize();
                m_radius = std::min(size.x, size.y) * 0.5f;
                m_center += size * 0.5f;
            }
        }
    }

    bool CircleCollider::checkCollision(const Collider *other, CollisionInfo &info) const
    {
        if (!canCollideWith(other))
            return false;

        switch (other->getType())
        {
        case ColliderType::Circle:
            return checkCirclevsCircle(static_cast<const CircleCollider *>(other), info);
        case ColliderType::AABB:
            return checkCirclevsAABB(static_cast<const AABBCollider *>(other), info);
        default:
            return false;
        }
    }

    bool CircleCollider::checkCirclevsCircle(const CircleCollider *other, CollisionInfo &info) const
    {
        glm::vec2 distance = other->m_center - m_center;
        float distanceLength = std::sqrt(distance.x * distance.x + distance.y * distance.y);
        float combinedRadius = m_radius + other->m_radius;

        if (distanceLength <= combinedRadius)
        {
            info.other = const_cast<CircleCollider *>(other);
            info.otherGameObject = other->m_gameObject;
            info.penetration = combinedRadius - distanceLength;

            if (distanceLength > 0.0f)
            {
                info.normal = distance / distanceLength;
                info.point = m_center + info.normal * m_radius;
            }
            else
            {

                info.normal = glm::vec2(1.0f, 0.0f);
                info.point = m_center;
            }

            return true;
        }

        return false;
    }

    bool CircleCollider::checkCirclevsAABB(const AABBCollider *other, CollisionInfo &info) const
    {

        CollisionInfo tempInfo;
        bool collision = other->checkAABBvsCircle(this, tempInfo);

        if (collision)
        {
            info = tempInfo;
            info.other = const_cast<CircleCollider *>(this);
            info.otherGameObject = getGameObjectPtr();
            info.normal = -info.normal;
        }

        return collision;
    }
}