#pragma once

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
    };
}