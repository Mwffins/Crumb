#pragma once
#include "Core/Application.h"
#include "Scene/Scene.h"
#include <memory>

namespace TestGame
{
    namespace cr = Crumb;

    class TestApplication : public cr::Application
    {
    private:
        std::unique_ptr<cr::Scene> m_currentScene;

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
    };
}