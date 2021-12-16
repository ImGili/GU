/*
 * @Author: ImGili
 * @Description: 
 */
#pragma once
#include<GLFW/glfw3.h>
namespace GU
{
    using MouseKeyCode = uint32_t;
    namespace MouseKey
    {
        enum : MouseKeyCode
        {
            ButtonMiddle = GLFW_MOUSE_BUTTON_MIDDLE,
            ButtonLeft = GLFW_MOUSE_BUTTON_LEFT,
            ButtonRight = GLFW_MOUSE_BUTTON_RIGHT
        };
    }
}
