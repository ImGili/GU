/*
 * @Author: ImGili
 * @Description: 
 */
#pragma once
#include"Core/Core.h"
#include<GLFW/glfw3.h>
#include<glm/glm.hpp>
#include"Core/KeyCode.h"
#include"Core/MouseCode.h"
namespace GU
{
    
    class GU_API Input
    {
    public:
        static bool IsKeyPressed(const KeyCode keycode);
        static bool IsMousePressed(const MouseKeyCode mousecode);
        static glm::vec2 GetMoudsePosition();
    };
}
