/*
 * @Author: ImGili
 * @Description: 
 */
#include"WindowsWindow.h"
#include"Events/ApplicationEvent.h"
#include<iostream>
using namespace GU;
WindowsWindow::WindowsWindow(const WindowProps& props)
{
    Init(props);
}
void WindowsWindow::OnUpdate()
{
    glfwPollEvents();
    glfwSwapBuffers(m_window);
}
void WindowsWindow::Init(const WindowProps& props)
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // glfw window creation
    // --------------------
    m_window = glfwCreateWindow(props.Width, props.Width, (props.Title).c_str(), NULL, NULL);
    glfwMakeContextCurrent(m_window);
   
    m_Context = GraphicsContext::Create(m_window);
    m_Context->Init();
    
    // if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    // {
    //     std::cout << "Failed to initialize GLAD" << std::endl;
    //     return;
    // }

    glfwSetWindowUserPointer(m_window, &m_wData);
    
    glfwSetWindowCloseCallback(m_window, [](GLFWwindow* window){
        WindowData& wData =  *(WindowData*)glfwGetWindowUserPointer(window);
        WindowsClosedEvnet event;
        wData.callback(event);
    });
}

WindowsWindow::~WindowsWindow()
{
    glfwDestroyWindow(m_window);

    glfwTerminate();
}

void WindowsWindow::SetEventCallback(const EventCallbackFn& callback)
{
    m_wData.callback = callback;
}


void* WindowsWindow::GetNativeWindow()
{
    return (void*) m_window;
}
