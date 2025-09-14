#pragma once
#include <vector>
#include <memory>
#include <string>
#include <unordered_map>
#include "GameObject.h"
#include "../Core/Event.h"

namespace Crumb
{
    class Renderer2D;
    class Application;
    
    class Scene
    {
    private:
        std::vector<std::unique_ptr<GameObject>> m_gameObjects;
        std::unordered_map<std::string, GameObject*> m_namedObjects;
        std::string m_name;
        bool m_initialized;
        
    public:
        Scene(const std::string& name = "Scene");
        virtual ~Scene();
        
        virtual void initialize();
        virtual void update(float deltaTime);
        virtual void render(Renderer2D* renderer);
        virtual void shutdown();
        
        template<typename T, typename... Args>
        T* createGameObject(const std::string& name, Args&&... args);
        
        void addGameObject(std::unique_ptr<GameObject> gameObject);
        GameObject* findGameObject(const std::string& name) const;
        void removeGameObject(const std::string& name);
        void removeGameObject(GameObject* gameObject);
        
        bool dispatchKeyPressed(const KeyPressedEvent& event);
        bool dispatchKeyReleased(const KeyReleasedEvent& event);
        bool dispatchMouseButtonPressed(const MouseButtonPressedEvent& event);
        bool dispatchMouseButtonReleased(const MouseButtonReleasedEvent& event);
        bool dispatchMouseMoved(const MouseMovedEvent& event);
        bool dispatchMouseScrolled(const MouseScrolledEvent& event);
        
        const std::string& getName() const { return m_name; }
        size_t getGameObjectCount() const { return m_gameObjects.size(); }
        
        template<typename T>
        std::vector<T*> getGameObjectsOfType() const;
    };
    
    template<typename T, typename... Args>
    T* Scene::createGameObject(const std::string& name, Args&&... args)
    {
        static_assert(std::is_base_of<GameObject, T>::value, "T must inherit from GameObject");
        
        auto gameObject = std::make_unique<T>(name, std::forward<Args>(args)...);
        T* ptr = gameObject.get();
        
        gameObject->setScene(this);
        m_namedObjects[name] = ptr;
        m_gameObjects.push_back(std::move(gameObject));
        
        if (m_initialized)
        {
            ptr->initialize();
        }
        
        return ptr;
    }
    
    template<typename T>
    std::vector<T*> Scene::getGameObjectsOfType() const
    {
        std::vector<T*> result;
        for (const auto& gameObject : m_gameObjects)
        {
            if (T* casted = dynamic_cast<T*>(gameObject.get()))
            {
                result.push_back(casted);
            }
        }
        return result;
    }
}