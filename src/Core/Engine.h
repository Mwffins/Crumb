#pragma once
#include <iostream>
#include <memory>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Crumb
{
    class Application;
    class Renderer2D;

    enum class ProjectionMode
    {
        Orthographic2D,
        Orthographic2DCenter,
        Custom
    };

    class Engine
    {
    private:
        GLFWwindow *m_window;
        bool m_running;
        double m_deltaTime;
        double m_lastFrame;

        int m_windowWidth;
        int m_windowHeight;

        std::unique_ptr<Application> m_application;

        std::unique_ptr<Renderer2D> m_renderer;

        glm::mat4 m_projectionMatrix;
        ProjectionMode m_projectionMode;
        bool m_autoUpdateProjection;

        bool initializeWindow();
        [[nodiscard]] bool initializeOpenGL() const;
        void calculateDeltaTime();
        void updateProjectionMatrix();

        float m_targetFPS;
        float m_targetFrameTime;
        bool m_vsyncEnabled;

    public:
        explicit Engine(int width = 720, int height = 520, const std::string &title = "Crumb Engine");
        ~Engine();

        bool initialize();
        void run();
        void shutdown();

        [[nodiscard]] GLFWwindow *getWindow() const { return m_window; }
        [[nodiscard]] float getDeltaTime() const { return m_deltaTime; }
        [[nodiscard]] int getWindowWidth() const { return m_windowWidth; }
        [[nodiscard]] int getWindowHeight() const { return m_windowHeight; }

        void setApplication(std::unique_ptr<Application> app);

        void requestClose() { m_running = false; }

        void setTargetFPS(float fps);
        void setVSync(bool enabled);
        [[nodiscard]] float getCurrentFPS() const;

        [[nodiscard]] glm::mat4 getProjectionMatrix() const { return m_projectionMatrix; }
        void setProjectionMode(ProjectionMode mode);
        void setCustomProjection(const glm::mat4 &projection);
        void setAutoUpdateProjection(bool autoUpdate) { m_autoUpdateProjection = autoUpdate; }

        [[nodiscard]] Renderer2D *getRenderer() const { return m_renderer.get(); }

    private:
        static void framebufferSizeCallback(GLFWwindow *window, int width, int height);
        static void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods);
    };
}