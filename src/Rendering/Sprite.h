#pragma once
#include <glm/glm.hpp>
#include <string>

namespace Crumb
{

    class Sprite
    {
    public:
        Sprite(const std::string &textureName, const glm::vec2 &position, const glm::vec2 &size);

        void setPosition(const glm::vec2 &pos);
        void setSize(const glm::vec2 &size);

        const glm::vec2 &getPosition() const;
        const glm::vec2 &getSize() const;
        unsigned int getTextureID() const;

    private:
        unsigned int m_textureID;
        glm::vec2 m_position;
        glm::vec2 m_size;
    };
}