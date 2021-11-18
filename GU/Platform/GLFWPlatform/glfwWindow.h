/*
 * @Author: ImGili
 * @Description: 
 */
#pragma once
#include"Core/Core.h"
#include"Core/Window.h"
#include"GLFW/glfw3.h"
#include"Renderer/GraphicsContext.h"
namespace GU
{
    class GU_API glfwWindow : public Window
    {
    public:
        glfwWindow(const WindowProps& props);
        virtual void OnUpdate() override;
    private:
        GLFWwindow* m_window;
        void Init(const WindowProps& props);
        void SetEventCallback(const EventCallbackFn& callback) override;
        void* GetNativeWindow() override
        {
            return (void*)m_window;
        }
        void MaxWindow() override;
        WindowData m_wData;
        std::unique_ptr<GraphicsContext> m_Context;
    };
}