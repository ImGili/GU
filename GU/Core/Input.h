/*
 * @Author: ImGili
 * @Description: 
 */
#pragma once
#include"Core/Core.h"
#include<GLFW/glfw3.h>
#include<glm/glm.hpp>
namespace GU
{
    enum class KeyCode
    {
        W = GLFW_KEY_W,
        A = GLFW_KEY_A,
        S = GLFW_KEY_S,
        D = GLFW_KEY_D,
        LeftAlt = GLFW_KEY_LEFT_ALT
    };

    enum class MouseKeyCode
    {
        ButtonMiddle = GLFW_MOUSE_BUTTON_MIDDLE,
        ButtonLeft = GLFW_MOUSE_BUTTON_LEFT,
        ButtonRight = GLFW_MOUSE_BUTTON_RIGHT
    };
    class GU_API Input
    {
    public:
        static bool IsKeyPressed(const KeyCode);
        static bool IsMousePressed(const MouseKeyCode);
        static glm::vec2 GetMoudsePosition();
    };
}
