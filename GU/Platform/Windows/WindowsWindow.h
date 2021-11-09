#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include"Core/Core.h"
#include"Core/Window.h"
namespace GU
{
    class GU_API WindowsWindow : public Window
    {
    public:
        WindowsWindow(const WindowProps& props);
        virtual void OnUpdate() override;
        void Clear(float r, float g, float b, float a) override;
        ~WindowsWindow();
    private:
        GLFWwindow* m_window;
        void Init(const WindowProps& props);
        void SetEventCallback(const EventCallbackFn& callback) override;
        WindowData m_wData;
        virtual void* GetNativeWindow() override;
    };
}