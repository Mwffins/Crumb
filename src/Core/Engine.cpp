#include "Engine.h"
#include "Application.h"

namespace Crumb {
    
    Engine::Engine(int width, int height, const std::string& title) 
        : m_window(nullptr), m_running(false), m_deltaTime(0.0f), m_lastFrame(0.0f),
          m_windowWidth(width), m_windowHeight(height) {
    }
    
    Engine::~Engine() {
        shutdown();
    }
    
    bool Engine::initialize() {
        if (!initializeWindow()) {
            return false;
        }
        
        if (!initializeOpenGL()) {
            return false;
        }
        
        std::cout << "Crumb Engine initialized successfully!" << std::endl;
        return true;
    }
    
    bool Engine::initializeWindow() {
        if (!glfwInit()) {
            std::cout << "Failed to initialize GLFW" << std::endl;
            return false;
        }
        
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        
        m_window = glfwCreateWindow(m_windowWidth, m_windowHeight, "Crumb Engine", NULL, NULL);
        if (!m_window) {
            std::cout << "Failed to create GLFW window" << std::endl;
            glfwTerminate();
            return false;
        }
        
        glfwMakeContextCurrent(m_window);
        
        glfwSetWindowUserPointer(m_window, this);
        glfwSetFramebufferSizeCallback(m_window, framebufferSizeCallback);
        glfwSetKeyCallback(m_window, keyCallback);
        
        return true;
    }
    
    bool Engine::initializeOpenGL() {
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
            std::cout << "Failed to initialize GLAD" << std::endl;
            return false;
        }
        
        glViewport(0, 0, m_windowWidth, m_windowHeight);
        
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        
        return true;
    }
    
    void Engine::run() {
        if (!m_window || !m_application) {
            std::cout << "Engine not properly initialized or no application set!" << std::endl;
            return;
        }
        
        m_running = true;
        m_lastFrame = glfwGetTime();
        
        m_application->initialize();
        
        while (m_running && !glfwWindowShouldClose(m_window)) {
            calculateDeltaTime();
            
            glfwPollEvents();
            
            m_application->update(m_deltaTime);
            
            glClear(GL_COLOR_BUFFER_BIT);
            m_application->render();
            
            glfwSwapBuffers(m_window);
        }
        
        m_application->shutdown();
    }
    
    void Engine::shutdown() {
        if (m_window) {
            glfwDestroyWindow(m_window);
            m_window = nullptr;
        }
        glfwTerminate();
        std::cout << "Crumb Engine shut down." << std::endl;
    }
    
    void Engine::setApplication(std::unique_ptr<Application> app) {
        m_application = std::move(app);
        if (m_application) {
            m_application->setEngine(this);
        }
    }
    
    void Engine::calculateDeltaTime() {
        float current_frame = glfwGetTime();
        m_deltaTime = current_frame - m_lastFrame;
        m_lastFrame = current_frame;
    }
    
    void Engine::framebufferSizeCallback(GLFWwindow* window, int width, int height) {
        Engine* engine = static_cast<Engine*>(glfwGetWindowUserPointer(window));
        engine->m_windowWidth = width;
        engine->m_windowHeight = height;
        glViewport(0, 0, width, height);
    }
    
    void Engine::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
        Engine* engine = static_cast<Engine*>(glfwGetWindowUserPointer(window));
        
        if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
            engine->requestClose();
        }
        
        if (engine->m_application) {
            engine->m_application->onKeyEvent(key, scancode, action, mods);
        }
    }
}