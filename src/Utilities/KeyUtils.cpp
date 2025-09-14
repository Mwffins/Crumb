#include "KeyUtils.h"
#include <unordered_map>

namespace Crumb
{
    namespace KeyUtils
    {
        static std::unordered_map<int, std::string> s_keyNames = {
            {GLFW_KEY_SPACE, "Space"},
            {GLFW_KEY_APOSTROPHE, "'"},
            {GLFW_KEY_COMMA, ","},
            {GLFW_KEY_MINUS, "-"},
            {GLFW_KEY_PERIOD, "."},
            {GLFW_KEY_SLASH, "/"},
            {GLFW_KEY_SEMICOLON, ";"},
            {GLFW_KEY_EQUAL, "="},
            {GLFW_KEY_LEFT_BRACKET, "["},
            {GLFW_KEY_BACKSLASH, "\\"},
            {GLFW_KEY_RIGHT_BRACKET, "]"},
            {GLFW_KEY_GRAVE_ACCENT, "`"},
            
            {GLFW_KEY_ESCAPE, "Escape"},
            {GLFW_KEY_ENTER, "Enter"},
            {GLFW_KEY_TAB, "Tab"},
            {GLFW_KEY_BACKSPACE, "Backspace"},
            {GLFW_KEY_INSERT, "Insert"},
            {GLFW_KEY_DELETE, "Delete"},
            {GLFW_KEY_PAGE_UP, "Page Up"},
            {GLFW_KEY_PAGE_DOWN, "Page Down"},
            {GLFW_KEY_HOME, "Home"},
            {GLFW_KEY_END, "End"},
            {GLFW_KEY_CAPS_LOCK, "Caps Lock"},
            {GLFW_KEY_SCROLL_LOCK, "Scroll Lock"},
            {GLFW_KEY_NUM_LOCK, "Num Lock"},
            {GLFW_KEY_PRINT_SCREEN, "Print Screen"},
            {GLFW_KEY_PAUSE, "Pause"},
            
            {GLFW_KEY_RIGHT, "Right Arrow"},
            {GLFW_KEY_LEFT, "Left Arrow"},
            {GLFW_KEY_DOWN, "Down Arrow"},
            {GLFW_KEY_UP, "Up Arrow"},
            
            {GLFW_KEY_LEFT_SHIFT, "Left Shift"},
            {GLFW_KEY_LEFT_CONTROL, "Left Ctrl"},
            {GLFW_KEY_LEFT_ALT, "Left Alt"},
            {GLFW_KEY_LEFT_SUPER, "Left Super"},
            {GLFW_KEY_RIGHT_SHIFT, "Right Shift"},
            {GLFW_KEY_RIGHT_CONTROL, "Right Ctrl"},
            {GLFW_KEY_RIGHT_ALT, "Right Alt"},
            {GLFW_KEY_RIGHT_SUPER, "Right Super"},
            
            {GLFW_KEY_KP_0, "Keypad 0"},
            {GLFW_KEY_KP_1, "Keypad 1"},
            {GLFW_KEY_KP_2, "Keypad 2"},
            {GLFW_KEY_KP_3, "Keypad 3"},
            {GLFW_KEY_KP_4, "Keypad 4"},
            {GLFW_KEY_KP_5, "Keypad 5"},
            {GLFW_KEY_KP_6, "Keypad 6"},
            {GLFW_KEY_KP_7, "Keypad 7"},
            {GLFW_KEY_KP_8, "Keypad 8"},
            {GLFW_KEY_KP_9, "Keypad 9"},
            {GLFW_KEY_KP_DECIMAL, "Keypad ."},
            {GLFW_KEY_KP_DIVIDE, "Keypad /"},
            {GLFW_KEY_KP_MULTIPLY, "Keypad *"},
            {GLFW_KEY_KP_SUBTRACT, "Keypad -"},
            {GLFW_KEY_KP_ADD, "Keypad +"},
            {GLFW_KEY_KP_ENTER, "Keypad Enter"},
            {GLFW_KEY_KP_EQUAL, "Keypad ="}
        };
        
        static std::unordered_map<int, std::string> s_mouseButtonNames = {
            {GLFW_MOUSE_BUTTON_LEFT, "Left Mouse"},
            {GLFW_MOUSE_BUTTON_RIGHT, "Right Mouse"},
            {GLFW_MOUSE_BUTTON_MIDDLE, "Middle Mouse"},
            {GLFW_MOUSE_BUTTON_4, "Mouse Button 4"},
            {GLFW_MOUSE_BUTTON_5, "Mouse Button 5"},
            {GLFW_MOUSE_BUTTON_6, "Mouse Button 6"},
            {GLFW_MOUSE_BUTTON_7, "Mouse Button 7"},
            {GLFW_MOUSE_BUTTON_8, "Mouse Button 8"}
        };

        std::string keyToString(int key)
        {
            auto it = s_keyNames.find(key);
            if (it != s_keyNames.end())
            {
                return it->second;
            }
            
            if (key >= GLFW_KEY_A && key <= GLFW_KEY_Z)
            {
                return std::string(1, 'A' + (key - GLFW_KEY_A));
            }
            
            if (key >= GLFW_KEY_0 && key <= GLFW_KEY_9)
            {
                return std::string(1, '0' + (key - GLFW_KEY_0));
            }
            
            if (key >= GLFW_KEY_F1 && key <= GLFW_KEY_F12)
            {
                return "F" + std::to_string(key - GLFW_KEY_F1 + 1);
            }
            
            if (key >= GLFW_KEY_F13 && key <= GLFW_KEY_F25)
            {
                return "F" + std::to_string(key - GLFW_KEY_F13 + 13);
            }
            
            return "Key " + std::to_string(key);
        }

        std::string mouseButtonToString(int button)
        {
            auto it = s_mouseButtonNames.find(button);
            if (it != s_mouseButtonNames.end())
            {
                return it->second;
            }
            
            return "Mouse Button " + std::to_string(button);
        }

        bool isLetterKey(int key)
        {
            return key >= GLFW_KEY_A && key <= GLFW_KEY_Z;
        }

        bool isNumberKey(int key)
        {
            return key >= GLFW_KEY_0 && key <= GLFW_KEY_9;
        }

        bool isFunctionKey(int key)
        {
            return (key >= GLFW_KEY_F1 && key <= GLFW_KEY_F12) ||
                   (key >= GLFW_KEY_F13 && key <= GLFW_KEY_F25);
        }

        bool isArrowKey(int key)
        {
            return key == GLFW_KEY_UP || key == GLFW_KEY_DOWN ||
                   key == GLFW_KEY_LEFT || key == GLFW_KEY_RIGHT;
        }

        char getLetterFromKey(int key)
        {
            if (isLetterKey(key))
            {
                return 'A' + (key - GLFW_KEY_A);
            }
            return '\0';
        }

        char getNumberFromKey(int key)
        {
            if (isNumberKey(key))
            {
                return '0' + (key - GLFW_KEY_0);
            }
            return '\0';
        }
    }
}