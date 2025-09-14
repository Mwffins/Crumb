#pragma once
#include <glm/glm.hpp>
#include "Shader.h"

namespace Crumb
{

    class Sprite;
    struct QuadVertex;

    class Renderer2D
    {
    public:
        Renderer2D();
        ~Renderer2D();

        void begin();
        void drawSprite(const Sprite &sprite);
        void end();
        void flush();

        void setProjectionMatrix(const glm::mat4 &projection);

    private:
        void initializeShaders();

        unsigned int m_VAO, m_VBO, m_IBO;
        Shader m_shader;
        unsigned int m_whiteTexture;

        QuadVertex *m_quadBuffer;
        QuadVertex *m_quadBufferPtr;
        size_t m_quadCount;

        unsigned int m_textureSlots[32];
        uint32_t m_textureSlotIndex;

        glm::mat4 m_projectionMatrix;

        static const size_t MAX_QUADS;
        static const size_t MAX_VERTICES;
        static const size_t MAX_INDICES;
        static const size_t MAX_TEXTURE_SLOTS;
    };
}