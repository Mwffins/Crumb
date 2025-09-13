#include "Core/Application.h"
#include "Rendering/Shader.h"
#include <glad/glad.h>

namespace Crumb {
    class TestApplication : public Application {
    private:
        Shader m_shader;
        unsigned int m_VAO, m_VBO, m_EBO;
        unsigned int m_texture;
        
        float m_projection[16];
        float m_model[16];
        
    public:
        bool initialize() override {
            if (!m_shader.LoadFromFiles("assets/shaders/vertex.glsl", "assets/shaders/fragment.glsl")) {
                std::cout << "Failed to load shaders!" << std::endl;
                return false;
            }
            
            setupQuad();
            createTexture();
            setupMatrices();
            
            glClearColor(0.76f, 0.60f, 0.42f, 1.0f);
            
            return true;
        }
        
        void update(float delta_time) override {

        }
        
        void render() override {
            m_shader.Use();
            
            glUniformMatrix4fv(glGetUniformLocation(m_shader.GetProgramID(), "projection"), 1, GL_FALSE, m_projection);
            glUniformMatrix4fv(glGetUniformLocation(m_shader.GetProgramID(), "model"), 1, GL_FALSE, m_model);
            
            m_shader.SetVec4("spriteColor", 1.0f, 0.5f, 0.2f, 1.0f);
            
            glBindTexture(GL_TEXTURE_2D, m_texture);
            glBindVertexArray(m_VAO);
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        }
        
        void shutdown() override {
            glDeleteVertexArrays(1, &m_VAO);
            glDeleteBuffers(1, &m_VBO);
            glDeleteBuffers(1, &m_EBO);
            glDeleteTextures(1, &m_texture);
        }
        
    private:
        void setupQuad() {
            float vertices[] = {
                -0.5f, -0.5f,    0.0f, 0.0f,
                 0.5f, -0.5f,    1.0f, 0.0f,
                 0.5f,  0.5f,    1.0f, 1.0f,
                -0.5f,  0.5f,    0.0f, 1.0f
            };

            unsigned int indices[] = {
                0, 1, 2,
                2, 3, 0
            };

            glGenVertexArrays(1, &m_VAO);
            glGenBuffers(1, &m_VBO);
            glGenBuffers(1, &m_EBO);

            glBindVertexArray(m_VAO);

            glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
            glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

            glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
            glEnableVertexAttribArray(0);

            glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
            glEnableVertexAttribArray(1);

            glBindVertexArray(0);
        }
        
        void createTexture() {
            glGenTextures(1, &m_texture);
            glBindTexture(GL_TEXTURE_2D, m_texture);
            
            unsigned char white_pixel[] = {255, 255, 255, 255}; // RGBA
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1, 1, 0, GL_RGBA, GL_UNSIGNED_BYTE, white_pixel);
            
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
            
            glBindTexture(GL_TEXTURE_2D, 0);
        }
        
        void setupMatrices() {
            int window_width = m_engine->getWindowWidth();
            int window_height = m_engine->getWindowHeight();
            
            m_projection[0] = 2.0f / window_width;   m_projection[1] = 0.0f;                    m_projection[2] = 0.0f;  m_projection[3] = 0.0f;
            m_projection[4] = 0.0f;                  m_projection[5] = 2.0f / window_height;   m_projection[6] = 0.0f;  m_projection[7] = 0.0f;
            m_projection[8] = 0.0f;                  m_projection[9] = 0.0f;                    m_projection[10] = -1.0f; m_projection[11] = 0.0f;
            m_projection[12] = -1.0f;                m_projection[13] = -1.0f;                  m_projection[14] = 0.0f; m_projection[15] = 1.0f;

            m_model[0] = 100.0f;  m_model[1] = 0.0f;    m_model[2] = 0.0f;  m_model[3] = 0.0f;
            m_model[4] = 0.0f;    m_model[5] = 100.0f;  m_model[6] = 0.0f;  m_model[7] = 0.0f;
            m_model[8] = 0.0f;    m_model[9] = 0.0f;    m_model[10] = 1.0f; m_model[11] = 0.0f;
            m_model[12] = 0.0f;   m_model[13] = 0.0f;   m_model[14] = 0.0f; m_model[15] = 1.0f;
        }
    };
}