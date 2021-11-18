/*
 * @Author: ImGili
 * @Description: 
 */
#include"Platform/GLFWPlatform/glfwWindow.h"
#include"Events/ApplicationEvent.h"
#include"Events/MouseEvent.h"
#include"Platform/OpenGL/OpenGLContext.h"
#include"Core/Log.h"
#include<iostream>
using namespace GU;
glfwWindow::glfwWindow(const WindowProps& props)
{
    Init(props);
}
void glfwWindow::OnUpdate()
{
    glfwPollEvents();
    glfwSwapBuffers(m_window);
}
void glfwWindow::Init(const WindowProps& props)
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    #ifdef GU_PLATFORM_MACOS
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    #endif
    
    glfwWindowHint(GLFW_SAMPLES, 4);

    // glfw window creation
    // --------------------
    m_window = glfwCreateWindow(props.Width, props.Width, (props.Title).c_str(), NULL, NULL);
    glfwMakeContextCurrent(m_window);
   
    m_Context = GraphicsContext::Create(m_window);
    m_Context->Init();
    
    glfwSetWindowUserPointer(m_window, &m_wData);
    
    glfwSetWindowCloseCallback(m_window, [](GLFWwindow* window){
        WindowData& wData =  *(WindowData*)glfwGetWindowUserPointer(window);
        WindowsClosedEvnet event;
        wData.callback(event);
    });

    glfwSetScrollCallback(m_window, [](GLFWwindow* window, double xOffset, double yOffset){
        GU_INFO("{0}",yOffset);
        WindowData& wData =  *(WindowData*)glfwGetWindowUserPointer(window);
        MouseScrolledEvent event((float)xOffset, (float)yOffset);
        wData.callback(event);});
}



void glfwWindow::SetEventCallback(const EventCallbackFn& callback)
{
    m_wData.callback = callback;
}

void glfwWindow::MaxWindow()
{
    // 获取当前屏幕（monitor）
    GLFWmonitor* monitor = glfwGetPrimaryMonitor();
    // 获取当前屏幕的模式
    const GLFWvidmode* mode = glfwGetVideoMode(monitor);
    glfwSetWindowMonitor(m_window, monitor, 0, 0, mode->width, mode->height, mode->refreshRate);
}