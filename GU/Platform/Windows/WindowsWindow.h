#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <memory>
#include"Core/Core.h"
#include"Core/Window.h"
#include"Renderer/GraphicsContext.h"
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
        void* GetNativeWindow() override;
        WindowData m_wData;
        std::unique_ptr<GraphicsContext> m_Context;
    };
}