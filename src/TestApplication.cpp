#include "TestApplication.h"
#include "Core/Engine.h"
#include "Core/AssetManager.h"
#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

namespace Crumb
{

    bool TestApplication::initialize()
    {
        AssetManager::get().loadTexture("player", "assets/sprites/player.png");

        m_renderer = std::make_unique<Renderer2D>();

        m_playerSprite = std::make_unique<Sprite>("player", glm::vec2(25.0f, 25.0f), glm::vec2(256.0f, 256.0f));

        int window_width = m_engine->getWindowWidth();
        int window_height = m_engine->getWindowHeight();
        glm::mat4 projection = glm::ortho(0.0f, (float)window_width, (float)window_height, 0.0f, -1.0f, 1.0f);
        m_renderer->setProjectionMatrix(projection);

        glClearColor(0.76f, 0.60f, 0.42f, 1.0f);

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        return true;
    }

    void TestApplication::update(float delta_time)
    {
    }

    void TestApplication::render()
    {
        glClear(GL_COLOR_BUFFER_BIT);

        m_renderer->begin();

        m_renderer->drawSprite(*m_playerSprite);

        m_renderer->end();
    }

    void TestApplication::shutdown()
    {
        m_renderer.reset();
        m_playerSprite.reset();
    }

}