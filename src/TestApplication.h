#pragma once
#include "Core/Application.h"
#include "Rendering/Renderer2D.h"
#include "Rendering/Sprite.h"
#include <memory>

namespace Crumb
{

    class TestApplication : public Application
    {
    private:
        std::unique_ptr<Renderer2D> m_renderer;
        std::unique_ptr<Sprite> m_playerSprite;

    public:
        bool initialize() override;
        void update(float delta_time) override;
        void render() override;
        void shutdown() override;
    };

}