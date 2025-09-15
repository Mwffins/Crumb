#include "SpriteGameObject.h"
#include "../Rendering/Renderer2D.h"

namespace Crumb
{
    SpriteGameObject::SpriteGameObject(const std::string& name, const glm::vec2& position, 
                                       const glm::vec2& size, const std::string& textureName)
        : GameObject(name, position, size), m_textureName(textureName)
    {
    }

    void SpriteGameObject::initialize()
    {
        m_sprite = std::make_unique<Sprite>(m_textureName, m_position, m_size);
    }

    void SpriteGameObject::render(Renderer2D* renderer)
    {
        if (m_sprite)
        {
            renderer->drawSprite(*m_sprite);
        }
    }

    void SpriteGameObject::shutdown()
    {
        m_sprite.reset();
    }
}