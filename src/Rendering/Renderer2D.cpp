#include "Renderer2D.h"
#include "Sprite.h"
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

namespace Crumb
{

    struct QuadVertex
    {
        glm::vec2 position;
        glm::vec2 texCoords;
        float textureSlot;
    };

    const size_t Renderer2D::MAX_QUADS = 10000;
    const size_t Renderer2D::MAX_VERTICES = MAX_QUADS * 4;
    const size_t Renderer2D::MAX_INDICES = MAX_QUADS * 6;
    const size_t Renderer2D::MAX_TEXTURE_SLOTS = 32;

    Renderer2D::Renderer2D() : m_quadCount(0), m_textureSlotIndex(1)
    {
        glGenVertexArrays(1, &m_VAO);
        glBindVertexArray(m_VAO);

        glGenBuffers(1, &m_VBO);
        glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
        glBufferData(GL_ARRAY_BUFFER, MAX_VERTICES * sizeof(QuadVertex), nullptr, GL_DYNAMIC_DRAW);

        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(QuadVertex), (void *)offsetof(QuadVertex, position));
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(QuadVertex), (void *)offsetof(QuadVertex, texCoords));
        glEnableVertexAttribArray(1);

        glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, sizeof(QuadVertex), (void *)offsetof(QuadVertex, textureSlot));
        glEnableVertexAttribArray(2);

        uint32_t *indices = new uint32_t[MAX_INDICES];
        uint32_t offset = 0;
        for (size_t i = 0; i < MAX_INDICES; i += 6)
        {
            indices[i + 0] = offset + 0;
            indices[i + 1] = offset + 1;
            indices[i + 2] = offset + 2;
            indices[i + 3] = offset + 2;
            indices[i + 4] = offset + 3;
            indices[i + 5] = offset + 0;
            offset += 4;
        }

        glGenBuffers(1, &m_IBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, MAX_INDICES * sizeof(uint32_t), indices, GL_STATIC_DRAW);
        delete[] indices;

        m_quadBuffer = new QuadVertex[MAX_VERTICES];
        m_quadBufferPtr = m_quadBuffer;

        for (int i = 0; i < MAX_TEXTURE_SLOTS; i++)
        {
            m_textureSlots[i] = 0;
        }

        glGenTextures(1, &m_whiteTexture);
        glBindTexture(GL_TEXTURE_2D, m_whiteTexture);
        uint32_t whiteTextureData = 0xffffffff;
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, 1, 1, 0, GL_RGBA, GL_UNSIGNED_BYTE, &whiteTextureData);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        m_textureSlots[0] = m_whiteTexture;

        initializeShaders();

        glBindVertexArray(0);
    }

    Renderer2D::~Renderer2D()
    {
        delete[] m_quadBuffer;
        glDeleteVertexArrays(1, &m_VAO);
        glDeleteBuffers(1, &m_VBO);
        glDeleteBuffers(1, &m_IBO);
        glDeleteTextures(1, &m_whiteTexture);
    }

    void Renderer2D::begin()
    {
        m_quadBufferPtr = m_quadBuffer;
        m_quadCount = 0;
        m_textureSlotIndex = 1;
    }

    void Renderer2D::drawSprite(const Sprite &sprite)
    {
        if (m_quadCount >= MAX_QUADS || m_textureSlotIndex >= MAX_TEXTURE_SLOTS)
        {
            flush();
            begin();
        }

        const glm::vec2 &position = sprite.getPosition();
        const glm::vec2 &size = sprite.getSize();
        unsigned int textureID = sprite.getTextureID();

        float textureSlot = 0.0f;
        if (textureID != 0)
        {
            textureSlot = -1.0f;
            for (uint32_t i = 1; i < m_textureSlotIndex; i++)
            {
                if (m_textureSlots[i] == textureID)
                {
                    textureSlot = (float)i;
                    break;
                }
            }

            if (textureSlot == -1.0f)
            {
                if (m_textureSlotIndex >= MAX_TEXTURE_SLOTS)
                {
                    flush();
                    begin();
                    textureSlot = (float)m_textureSlotIndex;
                }
                else
                {
                    textureSlot = (float)m_textureSlotIndex;
                }
                m_textureSlots[m_textureSlotIndex] = textureID;
                m_textureSlotIndex++;
            }
        }

        m_quadBufferPtr->position = {position.x, position.y};
        m_quadBufferPtr->texCoords = {0.0f, 0.0f};
        m_quadBufferPtr->textureSlot = textureSlot;
        m_quadBufferPtr++;

        m_quadBufferPtr->position = {position.x + size.x, position.y};
        m_quadBufferPtr->texCoords = {1.0f, 0.0f};
        m_quadBufferPtr->textureSlot = textureSlot;
        m_quadBufferPtr++;

        m_quadBufferPtr->position = {position.x + size.x, position.y + size.y};
        m_quadBufferPtr->texCoords = {1.0f, 1.0f};
        m_quadBufferPtr->textureSlot = textureSlot;
        m_quadBufferPtr++;

        m_quadBufferPtr->position = {position.x, position.y + size.y};
        m_quadBufferPtr->texCoords = {0.0f, 1.0f};
        m_quadBufferPtr->textureSlot = textureSlot;
        m_quadBufferPtr++;

        m_quadCount++;
    }

    void Renderer2D::end()
    {
        flush();
    }

    void Renderer2D::flush()
    {
        if (m_quadCount == 0)
            return;

        uint32_t dataSize = (uint32_t)((uint8_t *)m_quadBufferPtr - (uint8_t *)m_quadBuffer);
        glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
        glBufferSubData(GL_ARRAY_BUFFER, 0, dataSize, m_quadBuffer);

        for (uint32_t i = 0; i < m_textureSlotIndex; i++)
        {
            glActiveTexture(GL_TEXTURE0 + i);
            glBindTexture(GL_TEXTURE_2D, m_textureSlots[i]);
        }

        m_shader.Use();
        glBindVertexArray(m_VAO);
        glDrawElements(GL_TRIANGLES, m_quadCount * 6, GL_UNSIGNED_INT, nullptr);

        m_quadCount = 0;
    }

    void Renderer2D::setProjectionMatrix(const glm::mat4 &projection)
    {
        m_projectionMatrix = projection;
        m_shader.Use();
        glUniformMatrix4fv(glGetUniformLocation(m_shader.GetProgramID(), "u_projection"), 1, GL_FALSE, &projection[0][0]);
    }

    void Renderer2D::initializeShaders()
    {
        bool success = m_shader.LoadFromFiles("assets/shaders/sprite.vert", "assets/shaders/sprite.frag");
        if (!success)
        {
            std::cerr << "Failed to load sprite shaders!" << std::endl;
            return;
        }

        m_shader.Use();

        for (int i = 0; i < MAX_TEXTURE_SLOTS; i++)
        {
            m_shader.SetInt("u_textures[" + std::to_string(i) + "]", i);
        }
    }
}