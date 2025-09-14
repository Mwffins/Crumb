#pragma once
#include <string>
#include <GLFW/glfw3.h>

namespace Crumb
{
    namespace KeyUtils
    {
        std::string keyToString(int key);

        std::string mouseButtonToString(int button);

        bool isLetterKey(int key);

        bool isNumberKey(int key);

        bool isFunctionKey(int key);

        bool isArrowKey(int key);

        char getLetterFromKey(int key);

        char getNumberFromKey(int key);
    }
}