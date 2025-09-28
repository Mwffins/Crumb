#include "Application.h"

namespace Crumb
{
    void Application::dispatchEvent(const Event &event)
    {
        if (const auto keyPressed = dynamic_cast<const KeyPressedEvent *>(&event))
        {
            onKeyPressed(*keyPressed);
        }
        else if (const auto keyReleased = dynamic_cast<const KeyReleasedEvent *>(&event))
        {
            onKeyReleased(*keyReleased);
        }
        else if (const auto mousePressed = dynamic_cast<const MouseButtonPressedEvent *>(&event))
        {
            onMouseButtonPressed(*mousePressed);
        }
        else if (const auto mouseReleased = dynamic_cast<const MouseButtonReleasedEvent *>(&event))
        {
            onMouseButtonReleased(*mouseReleased);
        }
        else if (const auto mouseMoved = dynamic_cast<const MouseMovedEvent *>(&event))
        {
            onMouseMoved(*mouseMoved);
        }
        else if (const auto mouseScrolled = dynamic_cast<const MouseScrolledEvent *>(&event))
        {
            onMouseScrolled(*mouseScrolled);
        }
    }
}