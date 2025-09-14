#pragma once
#include <glm/glm.hpp>
#include <string>
#include <memory>
#include <vector>
#include "../Core/Event.h"

namespace Crumb
{
    class Scene;
    class Renderer2D;
    
    class GameObject
    {
    protected:
        std::string m_name;
        glm::vec2 m_position;
        glm::vec2 m_size;
        bool m_active;
        Scene* m_scene;
        
    public:
        GameObject(const std::string& name = "GameObject", 
                  const glm::vec2& position = glm::vec2(0.0f), 
                  const glm::vec2& size = glm::vec2(32.0f));
        
        virtual ~GameObject() = default;
        
        virtual void initialize() {}
        virtual void update(float deltaTime) {}
        virtual void render(Renderer2D* renderer) {}
        virtual void shutdown() {}
        
        virtual bool onKeyPressed(const KeyPressedEvent& event) { return false; }
        virtual bool onKeyReleased(const KeyReleasedEvent& event) { return false; }
        virtual bool onMouseButtonPressed(const MouseButtonPressedEvent& event) { return false; }
        virtual bool onMouseButtonReleased(const MouseButtonReleasedEvent& event) { return false; }
        virtual bool onMouseMoved(const MouseMovedEvent& event) { return false; }
        virtual bool onMouseScrolled(const MouseScrolledEvent& event) { return false; }
        
        void setPosition(const glm::vec2& position) { m_position = position; }
        void setSize(const glm::vec2& size) { m_size = size; }
        void move(const glm::vec2& offset) { m_position += offset; }
        
        const glm::vec2& getPosition() const { return m_position; }
        const glm::vec2& getSize() const { return m_size; }
        
        void setActive(bool active) { m_active = active; }
        bool isActive() const { return m_active; }
        
        const std::string& getName() const { return m_name; }
        void setName(const std::string& name) { m_name = name; }
        
        void setScene(Scene* scene) { m_scene = scene; }
        Scene* getScene() const { return m_scene; }
        
        bool intersects(const GameObject& other) const;
        glm::vec2 getCenter() const { return m_position + (m_size * 0.5f); }
    };
}