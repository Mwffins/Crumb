#include "InputManager.h"
#include <glm/glm.hpp>

namespace Crumb
{
    GLFWwindow* InputManager::s_window = nullptr;
    std::unordered_map<int, InputState> InputManager::s_keyStates;
    std::unordered_map<int, InputState> InputManager::s_mouseButtonStates;
    glm::vec2 InputManager::s_mousePosition = {0.0f, 0.0f};
    glm::vec2 InputManager::s_mouseDelta = {0.0f, 0.0f};
    glm::vec2 InputManager::s_lastMousePosition = {0.0f, 0.0f};
    float InputManager::s_scrollOffset = 0.0f;

    void InputManager::initialize(GLFWwindow* window)
    {
        s_window = window;
        
        glfwSetMouseButtonCallback(window, [](GLFWwindow* window, int button, int action, int mods) {
            InputManager::onMouseButtonEvent(button, action, mods);
        });
        
        glfwSetScrollCallback(window, [](GLFWwindow* window, double xoffset, double yoffset) {
            InputManager::onScrollEvent(xoffset, yoffset);
        });
    }

    void InputManager::update()
    {
        if (!s_window) return;
        
        double x, y;
        glfwGetCursorPos(s_window, &x, &y);
        glm::vec2 newMousePos((float)x, (float)y);
        s_mouseDelta = newMousePos - s_lastMousePosition;
        s_lastMousePosition = s_mousePosition;
        s_mousePosition = newMousePos;
        
        for (auto& [key, state] : s_keyStates)
        {
            if (state == InputState::JustPressed)
                state = InputState::Held;
            else if (state == InputState::JustReleased)
                state = InputState::Released;
        }
        
        for (auto& [button, state] : s_mouseButtonStates)
        {
            if (state == InputState::JustPressed)
                state = InputState::Held;
            else if (state == InputState::JustReleased)
                state = InputState::Released;
        }
        
        s_scrollOffset = 0.0f;
    }

    void InputManager::shutdown()
    {
        s_keyStates.clear();
        s_mouseButtonStates.clear();
        s_window = nullptr;
    }

    bool InputManager::isKeyPressed(int key)
    {
        auto it = s_keyStates.find(key);
        return it != s_keyStates.end() && 
               (it->second == InputState::Pressed || it->second == InputState::Held || it->second == InputState::JustPressed);
    }

    bool InputManager::isKeyHeld(int key)
    {
        auto it = s_keyStates.find(key);
        return it != s_keyStates.end() && it->second == InputState::Held;
    }

    bool InputManager::isKeyJustPressed(int key)
    {
        auto it = s_keyStates.find(key);
        return it != s_keyStates.end() && it->second == InputState::JustPressed;
    }

    bool InputManager::isKeyJustReleased(int key)
    {
        auto it = s_keyStates.find(key);
        return it != s_keyStates.end() && it->second == InputState::JustReleased;
    }

    bool InputManager::isMouseButtonPressed(int button)
    {
        auto it = s_mouseButtonStates.find(button);
        return it != s_mouseButtonStates.end() && 
               (it->second == InputState::Pressed || it->second == InputState::Held || it->second == InputState::JustPressed);
    }

    bool InputManager::isMouseButtonHeld(int button)
    {
        auto it = s_mouseButtonStates.find(button);
        return it != s_mouseButtonStates.end() && it->second == InputState::Held;
    }

    bool InputManager::isMouseButtonJustPressed(int button)
    {
        auto it = s_mouseButtonStates.find(button);
        return it != s_mouseButtonStates.end() && it->second == InputState::JustPressed;
    }

    bool InputManager::isMouseButtonJustReleased(int button)
    {
        auto it = s_mouseButtonStates.find(button);
        return it != s_mouseButtonStates.end() && it->second == InputState::JustReleased;
    }

    glm::vec2 InputManager::getMousePosition()
    {
        return s_mousePosition;
    }

    glm::vec2 InputManager::getMouseDelta()
    {
        return s_mouseDelta;
    }

    float InputManager::getScrollOffset()
    {
        return s_scrollOffset;
    }

    void InputManager::onKeyEvent(int key, int scancode, int action, int mods)
    {
        if (action == GLFW_PRESS)
        {
            s_keyStates[key] = InputState::JustPressed;
        }
        else if (action == GLFW_RELEASE)
        {
            s_keyStates[key] = InputState::JustReleased;
        }
    }

    void InputManager::onMouseButtonEvent(int button, int action, int mods)
    {
        if (action == GLFW_PRESS)
        {
            s_mouseButtonStates[button] = InputState::JustPressed;
        }
        else if (action == GLFW_RELEASE)
        {
            s_mouseButtonStates[button] = InputState::JustReleased;
        }
    }

    void InputManager::onScrollEvent(double xoffset, double yoffset)
    {
        s_scrollOffset = (float)yoffset;
    }
}