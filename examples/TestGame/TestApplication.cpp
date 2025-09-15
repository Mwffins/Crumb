#include "TestApplication.h"
#include "Core/Engine.h"
#include "Core/AssetManager.h"
#include "Core/InputManager.h"
#include "Utilities/KeyUtils.h"
#include "Rendering/Renderer2D.h"
#include "Scene/Scene.h"
#include "GameObjects/Player.h"
#include "Scene/SpriteGameObject.h"
#include "Physics/CollisionManager.h"
#include "Physics/Collider.h"
#include <glad/glad.h>
#include <iostream>

namespace TestGame
{

    bool TestApplication::initialize()
    {

        cr::AssetManager::get().loadTexture("player", "assets/sprites/player.png");
        cr::AssetManager::get().loadTexture("wall", "assets/sprites/wall.png");
        cr::AssetManager::get().loadTexture("coin", "assets/sprites/coin.png");

        m_currentScene = std::make_unique<cr::Scene>("MainScene");
        m_collisionManager = std::make_unique<cr::CollisionManager>();

        Player *player = m_currentScene->createGameObject<Player>("MainPlayer",
                                                                  glm::vec2(100.0f, 100.0f),
                                                                  glm::vec2(64.0f, 64.0f));
        player->setSpeed(300.0f);

        auto playerCollider = std::make_shared<cr::CircleCollider>(player, glm::vec2(32, 32), 30.0f);
        playerCollider->setCollisionLayer(0);
        m_collisionManager->addCollider(playerCollider);

        createWall(glm::vec2(300.0f, 200.0f), glm::vec2(64.0f, 64.0f));
        createWall(glm::vec2(364.0f, 200.0f), glm::vec2(64.0f, 64.0f));
        createWall(glm::vec2(300.0f, 264.0f), glm::vec2(64.0f, 64.0f));

        createCoin(glm::vec2(200.0f, 150.0f));
        createCoin(glm::vec2(500.0f, 300.0f));
        createCoin(glm::vec2(150.0f, 400.0f));

        m_collisionManager->setGlobalCollisionEnterCallback(
            [this](cr::GameObject *a, cr::GameObject *b)
            {
                onCollisionEnter(a, b);
            });

        m_collisionManager->setGlobalCollisionExitCallback(
            [this](cr::GameObject *a, cr::GameObject *b)
            {
                onCollisionExit(a, b);
            });

        m_currentScene->initialize();

        glClearColor(0.2f, 0.3f, 0.4f, 1.0f);

        return true;
    }

    void TestApplication::render()
    {
        glClear(GL_COLOR_BUFFER_BIT);

        if (m_currentScene)
        {
            cr::Renderer2D *renderer = m_engine->getRenderer();
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

        if (m_collisionManager)
        {
            m_collisionManager->update();
        }
    }

    void TestApplication::shutdown()
    {
        if (m_collisionManager)
        {
            m_collisionManager->clearColliders();
            m_collisionManager.reset();
        }

        if (m_currentScene)
        {
            m_currentScene->shutdown();
            m_currentScene.reset();
        }
    }

    void TestApplication::createWall(const glm::vec2 &position, const glm::vec2 &size)
    {
        cr::SpriteGameObject *wall = m_currentScene->createGameObject<cr::SpriteGameObject>(
            "Wall_" + std::to_string(m_wallCount++), position, size, "wall");

        auto wallCollider = std::make_shared<cr::AABBCollider>(wall, glm::vec2(0, 0), size);
        wallCollider->setCollisionLayer(1);
        m_collisionManager->addCollider(wallCollider);
    }

    void TestApplication::createCoin(const glm::vec2 &position)
    {
        cr::SpriteGameObject *coin = m_currentScene->createGameObject<cr::SpriteGameObject>(
            "Coin_" + std::to_string(m_coinCount++), position, glm::vec2(32.0f, 32.0f), "coin");

        auto coinCollider = std::make_shared<cr::CircleCollider>(coin, glm::vec2(16, 16), 16.0f, true);
        coinCollider->setCollisionLayer(2);
        m_collisionManager->addCollider(coinCollider);
    }

    void TestApplication::onCollisionEnter(cr::GameObject *a, cr::GameObject *b)
    {
        std::string nameA = a->getName();
        std::string nameB = b->getName();

        if ((nameA == "MainPlayer" && nameB.find("Coin_") == 0) ||
            (nameB == "MainPlayer" && nameA.find("Coin_") == 0))
        {
            std::string coinName = (nameA.find("Coin_") == 0) ? nameA : nameB;
            std::cout << "Player collected " << coinName << "!" << std::endl;

            m_currentScene->removeGameObject(coinName);
        }

        if ((nameA == "MainPlayer" && nameB.find("Wall_") == 0) ||
            (nameB == "MainPlayer" && nameA.find("Wall_") == 0))
        {
            std::cout << "Player hit a wall!" << std::endl;
        }
    }

    void TestApplication::onCollisionExit(cr::GameObject *a, cr::GameObject *b)
    {
    }

    bool TestApplication::onKeyPressed(const cr::KeyPressedEvent &event)
    {
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