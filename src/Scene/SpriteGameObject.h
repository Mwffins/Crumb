#pragma once
#include "GameObject.h"
#include "../Rendering/Sprite.h"
#include <memory>

namespace Crumb
{
    class SpriteGameObject : public GameObject
    {
    public:
        SpriteGameObject(const std::string& name, const glm::vec2& position, const glm::vec2& size, const std::string& textureName);
        
        void initialize() override;
        void render(Renderer2D* renderer) override;
        void shutdown() override;
        
    private:
        std::string m_textureName;
        std::unique_ptr<Sprite> m_sprite;
    };
}