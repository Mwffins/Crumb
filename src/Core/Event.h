#pragma once
#include <glm/glm.hpp>

namespace Crumb
{
    class Event
    {
    public:
        virtual ~Event() = default;
        bool handled = false;
    };

    class KeyEvent : public Event
    {
    public:
        int key;
        int scancode;
        int mods;

        KeyEvent(int k, int sc, int m) : key(k), scancode(sc), mods(m) {}
    };

    class KeyPressedEvent : public KeyEvent
    {
    public:
        KeyPressedEvent(int key, int scancode, int mods) : KeyEvent(key, scancode, mods) {}
    };

    class KeyReleasedEvent : public KeyEvent
    {
    public:
        KeyReleasedEvent(int key, int scancode, int mods) : KeyEvent(key, scancode, mods) {}
    };

    class MouseButtonEvent : public Event
    {
    public:
        int button;
        int mods;
        glm::vec2 position;

        MouseButtonEvent(int b, int m, const glm::vec2 &pos) : button(b), mods(m), position(pos) {}
    };

    class MouseButtonPressedEvent : public MouseButtonEvent
    {
    public:
        MouseButtonPressedEvent(int button, int mods, const glm::vec2 &pos)
            : MouseButtonEvent(button, mods, pos) {}
    };

    class MouseButtonReleasedEvent : public MouseButtonEvent
    {
    public:
        MouseButtonReleasedEvent(int button, int mods, const glm::vec2 &pos)
            : MouseButtonEvent(button, mods, pos) {}
    };

    class MouseMovedEvent : public Event
    {
    public:
        glm::vec2 position;
        glm::vec2 delta;

        MouseMovedEvent(const glm::vec2 &pos, const glm::vec2 &d) : position(pos), delta(d) {}
    };

    class MouseScrolledEvent : public Event
    {
    public:
        float xOffset;
        float yOffset;

        MouseScrolledEvent(float x, float y) : xOffset(x), yOffset(y) {}
    };
}