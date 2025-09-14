#include "Sprite.h"
#include "../Core/AssetManager.h"
#include <glad/glad.h>
#include <iostream>

namespace Crumb
{

    Sprite::Sprite(const std::string &textureName, const glm::vec2 &position, const glm::vec2 &size)
        : m_position(position), m_size(size)
    {
        m_textureID = AssetManager::get().getTexture(textureName);
        if (m_textureID == 0)
        {
            std::cerr << "Texture not found in AssetManager: " << textureName << std::endl;
        }
    }

    void Sprite::setPosition(const glm::vec2 &pos)
    {
        m_position = pos;
    }

    void Sprite::setSize(const glm::vec2 &size)
    {
        m_size = size;
    }

    const glm::vec2 &Sprite::getPosition() const
    {
        return m_position;
    }

    const glm::vec2 &Sprite::getSize() const
    {
        return m_size;
    }

    unsigned int Sprite::getTextureID() const
    {
        return m_textureID;
    }

}