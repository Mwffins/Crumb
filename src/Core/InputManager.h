#pragma once
#include <GLFW/glfw3.h>
#include <unordered_map>
#include <glm/glm.hpp>

namespace Crumb
{
    class Application;

    enum class InputState
    {
        Released,
        Pressed,
        Held,
        JustPressed,
        JustReleased
    };

    class InputManager
    {
    private:
        static GLFWwindow *s_window;
        static Application *s_application;
        static std::unordered_map<int, InputState> s_keyStates;
        static std::unordered_map<int, InputState> s_mouseButtonStates;
        static glm::vec2 s_mousePosition;
        static glm::vec2 s_mouseDelta;
        static glm::vec2 s_lastMousePosition;
        static float s_scrollOffset;

    public:
        static void initialize(GLFWwindow *window);
        static void setApplication(Application *app);
        static void update();
        static void shutdown();

        static bool isKeyPressed(int key);
        static bool isKeyHeld(int key);
        static bool isKeyJustPressed(int key);
        static bool isKeyJustReleased(int key);

        static bool isMouseButtonPressed(int button);
        static bool isMouseButtonHeld(int button);
        static bool isMouseButtonJustPressed(int button);
        static bool isMouseButtonJustReleased(int button);

        static glm::vec2 getMousePosition();
        static glm::vec2 getMouseDelta();
        static float getScrollOffset();

        static void onKeyEvent(int key, int scancode, int action, int mods);
        static void onMouseButtonEvent(int button, int action, int mods);
        static void onScrollEvent(double xoffset, double yoffset);

    private:
        static InputState updateInputState(InputState currentState, bool isCurrentlyPressed);
    };
}