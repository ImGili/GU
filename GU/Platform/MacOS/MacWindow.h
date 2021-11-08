/*
 * @Author: ImGili
 * @Description: 
 */
#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include"Core/Core.h"
#include"Core/Window.h"
namespace GU
{
    class GU_API MacWindow : public Window
    {
    public:
        MacWindow(const WindowProps& props);
        virtual void OnUpdate() override;
    private:
        GLFWwindow* m_window;
        void Init(const WindowProps& props);
        void SetEventCallback(const EventCallbackFn& callback) override;
        void* GetNativeWindow() override
        {
            return (void*)m_window;
        }
        WindowData m_wData;
    };
}