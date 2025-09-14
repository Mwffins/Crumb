#include "TestApplication.h"
#include "Core/Engine.h"
#include "Core/AssetManager.h"
#include "Core/InputManager.h"
#include "Utilities/KeyUtils.h"
#include "Rendering/Renderer2D.h"
#include <glad/glad.h>
#include <iostream>
#include <GLFW/glfw3.h>

namespace Crumb
{

    bool TestApplication::initialize()
    {
        AssetManager::get().loadTexture("player", "assets/sprites/player.png");

        m_playerSprite = std::make_unique<Sprite>("player", glm::vec2(25.0f, 25.0f), glm::vec2(256.0f, 256.0f));

        glClearColor(0.76f, 0.60f, 0.42f, 1.0f);

        std::cout << "TestApplication initialized! Engine handles renderer and projection automatically." << std::endl;
        return true;
    }

    void TestApplication::render()
    {
        glClear(GL_COLOR_BUFFER_BIT);

        Renderer2D *renderer = m_engine->getRenderer();

        renderer->begin();
        renderer->drawSprite(*m_playerSprite);
        renderer->end();
    }

    void TestApplication::update(float delta_time)
    {
    }

    void TestApplication::shutdown()
    {
        m_playerSprite.reset();
    }

    bool TestApplication::onKeyPressed(const KeyPressedEvent &event)
    {
        std::cout << "Key pressed: " << KeyUtils::keyToString(event.key) << std::endl;

        if (event.key == GLFW_KEY_1)
        {
            m_engine->setProjectionMode(ProjectionMode::Orthographic2D);
            std::cout << "Switched to Orthographic2D (top-left origin)" << std::endl;
        }
        else if (event.key == GLFW_KEY_2)
        {
            m_engine->setProjectionMode(ProjectionMode::Orthographic2DCenter);
            std::cout << "Switched to Orthographic2DCenter (centered origin)" << std::endl;
        }

        return false;
    }

}