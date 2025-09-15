#pragma once
#include "Core/Application.h"
#include "Scene/Scene.h"
#include "Physics/CollisionManager.h"
#include <memory>

namespace cr = Crumb;

namespace TestGame
{
    class TestApplication : public cr::Application
    {
    public:
        bool initialize() override;
        void render() override;
        void update(float delta_time) override;
        void shutdown() override;

        bool onKeyPressed(const cr::KeyPressedEvent &event) override;
        bool onKeyReleased(const cr::KeyReleasedEvent &event) override;
        bool onMouseButtonPressed(const cr::MouseButtonPressedEvent &event) override;
        bool onMouseButtonReleased(const cr::MouseButtonReleasedEvent &event) override;
        bool onMouseMoved(const cr::MouseMovedEvent &event) override;
        bool onMouseScrolled(const cr::MouseScrolledEvent &event) override;

    private:
        std::unique_ptr<cr::Scene> m_currentScene;
        std::unique_ptr<cr::CollisionManager> m_collisionManager;

        int m_wallCount = 0;
        int m_coinCount = 0;

        void createWall(const glm::vec2 &position, const glm::vec2 &size);
        void createCoin(const glm::vec2 &position);

        void onCollisionEnter(cr::GameObject *a, cr::GameObject *b);
        void onCollisionExit(cr::GameObject *a, cr::GameObject *b);
    };
}