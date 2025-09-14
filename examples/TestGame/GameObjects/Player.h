#pragma once
#include "Scene/GameObject.h"
#include "Rendering/Sprite.h"
#include <memory>

namespace TestGame
{
    namespace cr = Crumb;

    class Player : public cr::GameObject
    {
    private:
        std::unique_ptr<cr::Sprite> m_sprite;
        float m_speed;
        glm::vec2 m_velocity;

        bool m_movingUp, m_movingDown, m_movingLeft, m_movingRight;

    public:
        Player(const std::string &name = "Player",
               const glm::vec2 &position = glm::vec2(100.0f, 100.0f),
               const glm::vec2 &size = glm::vec2(64.0f, 64.0f));

        virtual ~Player() = default;

        void initialize() override;
        void update(float deltaTime) override;
        void render(cr::Renderer2D *renderer) override;
        void shutdown() override;

        bool onKeyPressed(const cr::KeyPressedEvent &event) override;
        bool onKeyReleased(const cr::KeyReleasedEvent &event) override;

        void setSpeed(float speed) { m_speed = speed; }
        float getSpeed() const { return m_speed; }

        const glm::vec2 &getVelocity() const { return m_velocity; }

    private:
        void updateMovement();
        void updateInput();
    };
}