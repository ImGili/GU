/*
 * @Author: ImGili
 * @Description: 
 */
#include"Application.h"
#include<iostream>
using namespace GU;

Application* Application::s_Instance = nullptr;

Application::Application()
{
    m_window = Window::Create();
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
    while (m_Running)
    {
        m_window->OnUpdate();
        m_imGuiLayer->Begin();
        for (auto it = m_Layers.begin(); it!=m_Layers.end(); it++)
        {
            (*it)->OnImGuiRender();
        }
        m_imGuiLayer->End();
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
}

