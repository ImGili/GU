/*
 * @Author: ImGili
 * @Description: 
 */
#include"MacWindow.h"
#include"Events/ApplicationEvent.h"
#include"Platform/OpenGL/OpenGLContext.h"
#include<iostream>
using namespace GU;
MacWindow::MacWindow(const WindowProps& props)
{
    Init(props);
}
void MacWindow::OnUpdate()
{
    glfwPollEvents();
    glfwSwapBuffers(m_window);
}
void MacWindow::Init(const WindowProps& props)
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_SAMPLES, 4);

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



void MacWindow::SetEventCallback(const EventCallbackFn& callback)
{
    m_wData.callback = callback;
}

void MacWindow::Clear(float r, float g, float b, float a)
{
    glClearColor(r, g, b, a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
}
