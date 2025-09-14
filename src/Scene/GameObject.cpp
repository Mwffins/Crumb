#include "GameObject.h"
#include <algorithm>

namespace Crumb
{
    GameObject::GameObject(const std::string &name, const glm::vec2 &position, const glm::vec2 &size)
        : m_name(name), m_position(position), m_size(size), m_active(true), m_scene(nullptr)
    {
    }

    bool GameObject::intersects(const GameObject &other) const
    {
        return (m_position.x < other.m_position.x + other.m_size.x &&
                m_position.x + m_size.x > other.m_position.x &&
                m_position.y < other.m_position.y + other.m_size.y &&
                m_position.y + m_size.y > other.m_position.y);
    }
}