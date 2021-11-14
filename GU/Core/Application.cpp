/*
 * @Author: ImGili
 * @Description: 
 */
#include"Application.h"
#include"Renderer/RenderCommand.h"
#include"Core/TimeStep.h"
#include<glfw/glfw3.h>
#include<iostream>
using namespace GU;

Application* Application::s_Instance = nullptr;

Application::Application()
{
    #ifdef GU_PLATFORM_WINDOWS
        m_window = Window::Create();
    #else
        m_window = Window::Create({"GUEngine", 640, 400});
    #endif
    
    m_window->SetEventCallback([this](Event& evnet){this->OnEvent(evnet);});
    if (s_Instance != nullptr)
    {
        GU_DEBUGBREAK();
    }
    s_Instance = this;
    m_imGuiLayer = new ImGuiLayer();
    m_imGuiLayer->OnAttach();
}
Application::~Application()
{
    
}

void Application::Run()
{
    m_LastFrameTime = (float)glfwGetTime();
    while (m_Running)
    {
        RenderCommand::Clear();
        m_imGuiLayer->Begin();
        float time = (float)glfwGetTime();
        TimeStep timestep = time - m_LastFrameTime;
        m_LastFrameTime = time;
        for (auto it = m_Layers.begin(); it!=m_Layers.end(); it++)
        {
            (*it)->OnUpdate(timestep);
        }
        for (auto it = m_Layers.begin(); it!=m_Layers.end(); it++)
        {
            (*it)->OnImGuiRender();
        }
        m_imGuiLayer->End();
        m_window->OnUpdate();
    }
    
}

void Application::OnEvent(Event& e)
{
    if(e.GetEvent() == EventType::WindowsCloseEvent)
        m_Running = false;
}

void Application::PushLayer(Layer* layer)
{
    m_Layers.push_back(layer);
    layer->OnAttach();
}

