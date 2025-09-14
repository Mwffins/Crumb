#include "Player.h"
#include <glad/glad.h>
#include "Core/AssetManager.h"
#include "Core/InputManager.h"
#include "Rendering/Renderer2D.h"
#include "Utilities/KeyUtils.h"
#include <iostream>

namespace TestGame
{
    Player::Player(const std::string &name, const glm::vec2 &position, const glm::vec2 &size)
        : cr::GameObject(name, position, size), m_speed(200.0f), m_velocity(0.0f),
          m_movingUp(false), m_movingDown(false), m_movingLeft(false), m_movingRight(false)
    {
    }

    void Player::initialize()
    {
        m_sprite = std::make_unique<cr::Sprite>("player", m_position, m_size);
    }

    void Player::update(float deltaTime)
    {
        updateInput();
        updateMovement();

        m_position += m_velocity * deltaTime;

        if (m_sprite)
        {
            m_sprite->setPosition(m_position);
        }
    }

    void Player::render(cr::Renderer2D *renderer)
    {
        if (m_sprite)
        {
            renderer->drawSprite(*m_sprite);
        }
    }

    void Player::shutdown()
    {
        m_sprite.reset();
    }

    bool Player::onKeyPressed(const cr::KeyPressedEvent &event)
    {
        return false;
    }

    bool Player::onKeyReleased(const cr::KeyReleasedEvent &event)
    {
        return false;
    }

    void Player::updateInput()
    {
        m_movingUp = cr::InputManager::isKeyPressed(GLFW_KEY_W) || cr::InputManager::isKeyPressed(GLFW_KEY_UP);
        m_movingDown = cr::InputManager::isKeyPressed(GLFW_KEY_S) || cr::InputManager::isKeyPressed(GLFW_KEY_DOWN);
        m_movingLeft = cr::InputManager::isKeyPressed(GLFW_KEY_A) || cr::InputManager::isKeyPressed(GLFW_KEY_LEFT);
        m_movingRight = cr::InputManager::isKeyPressed(GLFW_KEY_D) || cr::InputManager::isKeyPressed(GLFW_KEY_RIGHT);
    }

    void Player::updateMovement()
    {
        m_velocity = glm::vec2(0.0f);

        if (m_movingUp)
            m_velocity.y -= m_speed;
        if (m_movingDown)
            m_velocity.y += m_speed;
        if (m_movingLeft)
            m_velocity.x -= m_speed;
        if (m_movingRight)
            m_velocity.x += m_speed;

        if (m_velocity.x != 0.0f && m_velocity.y != 0.0f)
        {
            m_velocity *= 0.707f;
        }
    }
}