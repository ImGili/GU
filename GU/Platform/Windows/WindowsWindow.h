/*
 * @Author: ImGili
 * @Description: 
 */
#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include"Core.h"
#include"Window.h"
namespace GU
{
    class GU_API WindowsWindow : public Window
    {
    public:
        WindowsWindow(const WindowProps& props);
        virtual void OnUpdate() override;
        ~WindowsWindow();
    private:
        GLFWwindow* m_window;
        void Init(const WindowProps& props);
        void SetEventCallback(const EventCallbackFn& callback) override;
        WindowData m_wData;
        virtual void* GetNativeWindow();
    };
}