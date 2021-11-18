/*
 * @Author: ImGili
 * @Description: 
 */
#include"Window.h"
#include"Platform/GLFWPlatform/glfwWindow.h"
#include<memory>
#include<iostream>
namespace GU
{
    std::unique_ptr<Window> Window::Create(const WindowProps& props)
    {
        return std::make_unique<glfwWindow>(props);
    }
}
