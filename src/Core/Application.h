#pragma once
#include "Event.h"

namespace Crumb
{
    class Engine;

    class Application
    {
    protected:
        Engine *m_engine;

    public:
        Application() : m_engine(nullptr) {}
        virtual ~Application() = default;

        void setEngine(Engine *engine) { m_engine = engine; }

        virtual bool initialize() { return true; }
        virtual void update(float delta_time) {}
        virtual void render() {}
        virtual void shutdown() {}

        virtual bool onKeyPressed(const KeyPressedEvent &event) { return false; }
        virtual bool onKeyReleased(const KeyReleasedEvent &event) { return false; }
        virtual bool onMouseButtonPressed(const MouseButtonPressedEvent &event) { return false; }
        virtual bool onMouseButtonReleased(const MouseButtonReleasedEvent &event) { return false; }
        virtual bool onMouseMoved(const MouseMovedEvent &event) { return false; }
        virtual bool onMouseScrolled(const MouseScrolledEvent &event) { return false; }

        void dispatchEvent(const Event &event);
    };
}