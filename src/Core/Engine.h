#pragma once
#include <iostream>
#include <memory>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Crumb {
    class Application;

    class Engine {
    private:
        GLFWwindow* m_window;
        bool m_running;
        float m_deltaTime;
        float m_lastFrame;
        
        int m_windowWidth;
        int m_windowHeight;
        
        std::unique_ptr<Application> m_application;
        
        bool initializeWindow();
        bool initializeOpenGL();
        void calculateDeltaTime();
        
    public:
        Engine(int width = 720, int height = 520, const std::string& title = "Crumb Engine");
        ~Engine();
        
        bool initialize();
        void run();
        void shutdown();
        
        GLFWwindow* getWindow() const { return m_window; }
        float getDeltaTime() const { return m_deltaTime; }
        int getWindowWidth() const { return m_windowWidth; }
        int getWindowHeight() const { return m_windowHeight; }
        
        void setApplication(std::unique_ptr<Application> app);
        
        void requestClose() { m_running = false; }
        
    private:
        static void framebufferSizeCallback(GLFWwindow* window, int width, int height);
        static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
    };
}