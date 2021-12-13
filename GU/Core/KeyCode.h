/*
 * @Author: ImGili
 * @Description: 
 */
#pragma once
namespace GU
{
    using KeyCode = uint32_t;
    namespace Key
    {
        enum : KeyCode
        {
            W = GLFW_KEY_W,
            A = GLFW_KEY_A,
            S = GLFW_KEY_S,
            D = GLFW_KEY_D,
            O = GLFW_KEY_O,
            N = GLFW_KEY_N,
            R = GLFW_KEY_R,
            G = GLFW_KEY_G,
            LeftAlt = GLFW_KEY_LEFT_ALT,
            LeftCtrl = GLFW_KEY_LEFT_CONTROL,
            LeftShift = GLFW_KEY_LEFT_SHIFT,
        };
    }
}