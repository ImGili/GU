/*
 * @Author: ImGili
 * @Description: 
 */
#pragma once
#include"Core/Core.h"
#include<glfw/glfw3.h>
namespace GU
{
    enum KeyCode
    {
        W = GLFW_KEY_W,
        A = GLFW_KEY_A,
        S = GLFW_KEY_S,
        D = GLFW_KEY_D
    };

    class GU_API Input
    {
    public:
        static bool IsKeyPressed(const KeyCode);
    };
}
