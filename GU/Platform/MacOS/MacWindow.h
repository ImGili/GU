/*
 * @Author: ImGili
 * @Description: 
 */
#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <memory>
#include"Core/Core.h"
#include"Core/Window.h"
#include"Renderer/GraphicsContext.h"
namespace GU
{
    class GU_API MacWindow : public Window
    {
    public:
        MacWindow(const WindowProps& props);
        virtual void OnUpdate() override;
        void Clear(float r = 0.1f, float g = 0.1f, float b = 0.1f, float a = 0.1f) override;
    private:
        GLFWwindow* m_window;
        void Init(const WindowProps& props);
        void SetEventCallback(const EventCallbackFn& callback) override;
        void* GetNativeWindow() override
        {
            return (void*)m_window;
        }
        WindowData m_wData;
        std::unique_ptr<GraphicsContext> m_Context;
    };
}