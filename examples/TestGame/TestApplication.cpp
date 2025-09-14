#include "TestApplication.h"
#include "Core/Engine.h"
#include "Core/AssetManager.h"
#include "Core/InputManager.h"
#include "Utilities/KeyUtils.h"
#include "Rendering/Renderer2D.h"
#include "Scene/Scene.h"
#include "GameObjects/Player.h"
#include <glad/glad.h>
#include <iostream>

namespace TestGame
{

    bool TestApplication::initialize()
    {
        cr::AssetManager::get().loadTexture("player", "assets/sprites/player.png");

        m_currentScene = std::make_unique<cr::Scene>("MainScene");
        
        Player* player = m_currentScene->createGameObject<Player>("MainPlayer", 
                                                                  glm::vec2(100.0f, 100.0f), 
                                                                  glm::vec2(128.0f, 128.0f));
        player->setSpeed(300.0f);
        
        m_currentScene->initialize();

        glClearColor(0.76f, 0.60f, 0.42f, 1.0f);

        std::cout << "TestApplication initialized with Scene system!" << std::endl;
        return true;
    }

    void TestApplication::render()
    {
        glClear(GL_COLOR_BUFFER_BIT);

        if (m_currentScene)
        {
            cr::Renderer2D* renderer = m_engine->getRenderer();
            renderer->begin();
            m_currentScene->render(renderer);
            renderer->end();
        }
    }

    void TestApplication::update(float delta_time)
    {
        if (m_currentScene)
        {
            m_currentScene->update(delta_time);
        }
    }

    void TestApplication::shutdown()
    {
        if (m_currentScene)
        {
            m_currentScene->shutdown();
            m_currentScene.reset();
        }
    }

    bool TestApplication::onKeyPressed(const cr::KeyPressedEvent &event)
    {
        if (event.key == GLFW_KEY_1)
        {
            m_engine->setProjectionMode(cr::ProjectionMode::Orthographic2D);
            std::cout << "Switched to Orthographic2D (top-left origin)" << std::endl;
            return true;
        }
        else if (event.key == GLFW_KEY_2)
        {
            m_engine->setProjectionMode(cr::ProjectionMode::Orthographic2DCenter);
            std::cout << "Switched to Orthographic2DCenter (centered origin)" << std::endl;
            return true;
        }
        
        if (m_currentScene && m_currentScene->dispatchKeyPressed(event))
        {
            return true;
        }
        
        return false;
    }
    
    bool TestApplication::onKeyReleased(const cr::KeyReleasedEvent &event)
    {
        if (m_currentScene && m_currentScene->dispatchKeyReleased(event))
        {
            return true;
        }
        return false;
    }
    
    bool TestApplication::onMouseButtonPressed(const cr::MouseButtonPressedEvent &event)
    {
        if (m_currentScene && m_currentScene->dispatchMouseButtonPressed(event))
        {
            return true;
        }
        return false;
    }
    
    bool TestApplication::onMouseButtonReleased(const cr::MouseButtonReleasedEvent &event)
    {
        if (m_currentScene && m_currentScene->dispatchMouseButtonReleased(event))
        {
            return true;
        }
        return false;
    }
    
    bool TestApplication::onMouseMoved(const cr::MouseMovedEvent &event)
    {
        if (m_currentScene && m_currentScene->dispatchMouseMoved(event))
        {
            return true;
        }
        return false;
    }
    
    bool TestApplication::onMouseScrolled(const cr::MouseScrolledEvent &event)
    {
        if (m_currentScene && m_currentScene->dispatchMouseScrolled(event))
        {
            return true;
        }
        return false;
    }

}