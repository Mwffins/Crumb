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
        float m_deltaTime;
        float m_lastFrame;

        int m_windowWidth;
        int m_windowHeight;

        std::unique_ptr<Application> m_application;

        std::unique_ptr<Renderer2D> m_renderer;

        glm::mat4 m_projectionMatrix;
        ProjectionMode m_projectionMode;
        bool m_autoUpdateProjection;

        bool initializeWindow();
        bool initializeOpenGL();
        void calculateDeltaTime();
        void updateProjectionMatrix();

        float m_targetFPS;
        float m_targetFrameTime;
        bool m_vsyncEnabled;

    public:
        Engine(int width = 720, int height = 520, const std::string &title = "Crumb Engine");
        ~Engine();

        bool initialize();
        void run();
        void shutdown();

        GLFWwindow *getWindow() const { return m_window; }
        float getDeltaTime() const { return m_deltaTime; }
        int getWindowWidth() const { return m_windowWidth; }
        int getWindowHeight() const { return m_windowHeight; }

        void setApplication(std::unique_ptr<Application> app);

        void requestClose() { m_running = false; }

        void setTargetFPS(float fps);
        void setVSync(bool enabled);
        float getCurrentFPS() const;

        glm::mat4 getProjectionMatrix() const { return m_projectionMatrix; }
        void setProjectionMode(ProjectionMode mode);
        void setCustomProjection(const glm::mat4 &projection);
        void setAutoUpdateProjection(bool autoUpdate) { m_autoUpdateProjection = autoUpdate; }

        Renderer2D *getRenderer() const { return m_renderer.get(); }

    private:
        static void framebufferSizeCallback(GLFWwindow *window, int width, int height);
        static void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods);
    };
}