#include "Scene.h"
#include "../Rendering/Renderer2D.h"
#include <algorithm>
#include <iostream>

namespace Crumb
{
    Scene::Scene(const std::string& name)
        : m_name(name), m_initialized(false)
    {
    }
    
    Scene::~Scene()
    {
        shutdown();
    }
    
    void Scene::initialize()
    {
        if (m_initialized) return;
        
        for (auto& gameObject : m_gameObjects)
        {
            if (gameObject->isActive())
            {
                gameObject->initialize();
            }
        }
        
        m_initialized = true;
    }
    
    void Scene::update(float deltaTime)
    {
        if (!m_initialized) return;
        
        for (auto& gameObject : m_gameObjects)
        {
            if (gameObject->isActive())
            {
                gameObject->update(deltaTime);
            }
        }
    }
    
    void Scene::render(Renderer2D* renderer)
    {
        if (!m_initialized) return;
        
        for (auto& gameObject : m_gameObjects)
        {
            if (gameObject->isActive())
            {
                gameObject->render(renderer);
            }
        }
    }
    
    void Scene::shutdown()
    {
        if (!m_initialized) return;
        
        for (auto& gameObject : m_gameObjects)
        {
            gameObject->shutdown();
        }
        
        m_gameObjects.clear();
        m_namedObjects.clear();
        m_initialized = false;
    }
    
    void Scene::addGameObject(std::unique_ptr<GameObject> gameObject)
    {
        if (!gameObject) return;
        
        gameObject->setScene(this);
        m_namedObjects[gameObject->getName()] = gameObject.get();
        
        if (m_initialized && gameObject->isActive())
        {
            gameObject->initialize();
        }
        
        m_gameObjects.push_back(std::move(gameObject));
    }
    
    GameObject* Scene::findGameObject(const std::string& name) const
    {
        auto it = m_namedObjects.find(name);
        return (it != m_namedObjects.end()) ? it->second : nullptr;
    }
    
    void Scene::removeGameObject(const std::string& name)
    {
        auto it = m_namedObjects.find(name);
        if (it != m_namedObjects.end())
        {
            removeGameObject(it->second);
        }
    }
    
    void Scene::removeGameObject(GameObject* gameObject)
    {
        if (!gameObject) return;
        
        auto it = std::find_if(m_gameObjects.begin(), m_gameObjects.end(),
            [gameObject](const std::unique_ptr<GameObject>& obj) {
                return obj.get() == gameObject;
            });
        
        if (it != m_gameObjects.end())
        {
            (*it)->shutdown();
            m_namedObjects.erase((*it)->getName());
            m_gameObjects.erase(it);
        }
    }
    
    bool Scene::dispatchKeyPressed(const KeyPressedEvent& event)
    {
        for (auto& gameObject : m_gameObjects)
        {
            if (gameObject->isActive() && gameObject->onKeyPressed(event))
            {
                return true;
            }
        }
        return false;
    }
    
    bool Scene::dispatchKeyReleased(const KeyReleasedEvent& event)
    {
        for (auto& gameObject : m_gameObjects)
        {
            if (gameObject->isActive() && gameObject->onKeyReleased(event))
            {
                return true;
            }
        }
        return false;
    }
    
    bool Scene::dispatchMouseButtonPressed(const MouseButtonPressedEvent& event)
    {
        for (auto& gameObject : m_gameObjects)
        {
            if (gameObject->isActive() && gameObject->onMouseButtonPressed(event))
            {
                return true;
            }
        }
        return false;
    }
    
    bool Scene::dispatchMouseButtonReleased(const MouseButtonReleasedEvent& event)
    {
        for (auto& gameObject : m_gameObjects)
        {
            if (gameObject->isActive() && gameObject->onMouseButtonReleased(event))
            {
                return true;
            }
        }
        return false;
    }
    
    bool Scene::dispatchMouseMoved(const MouseMovedEvent& event)
    {
        for (auto& gameObject : m_gameObjects)
        {
            if (gameObject->isActive() && gameObject->onMouseMoved(event))
            {
                return true;
            }
        }
        return false;
    }
    
    bool Scene::dispatchMouseScrolled(const MouseScrolledEvent& event)
    {
        for (auto& gameObject : m_gameObjects)
        {
            if (gameObject->isActive() && gameObject->onMouseScrolled(event))
            {
                return true;
            }
        }
        return false;
    }
}