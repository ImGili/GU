/*
 * @Author: ImGili
 * @Description: 
 */
#include"Window.h"
#include"Platform/Windows/WindowsWindow.h"
#include"Platform/MacOS/MacWindow.h"
#include<memory>
#include<iostream>
namespace GU
{
    std::unique_ptr<Window> Window::Create(const WindowProps& props)
    {
        #ifdef GU_PLATFORM_WINDOWS
        return std::make_unique<WindowsWindow>(props);
        #elif GU_PLATFORM_MACOS
        return std::make_unique<MacWindow>(props);
        #endif
    }
}
