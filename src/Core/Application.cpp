#include "Application.h"

namespace Crumb
{
    void Application::dispatchEvent(const Event &event)
    {
        if (auto keyPressed = dynamic_cast<const KeyPressedEvent *>(&event))
        {
            onKeyPressed(*keyPressed);
        }
        else if (auto keyReleased = dynamic_cast<const KeyReleasedEvent *>(&event))
        {
            onKeyReleased(*keyReleased);
        }
        else if (auto mousePressed = dynamic_cast<const MouseButtonPressedEvent *>(&event))
        {
            onMouseButtonPressed(*mousePressed);
        }
        else if (auto mouseReleased = dynamic_cast<const MouseButtonReleasedEvent *>(&event))
        {
            onMouseButtonReleased(*mouseReleased);
        }
        else if (auto mouseMoved = dynamic_cast<const MouseMovedEvent *>(&event))
        {
            onMouseMoved(*mouseMoved);
        }
        else if (auto mouseScrolled = dynamic_cast<const MouseScrolledEvent *>(&event))
        {
            onMouseScrolled(*mouseScrolled);
        }
    }
}