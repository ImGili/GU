#pragma once
#include"Core.h"
#include"Window.h"
#include"Layer.h"
#include"ImGuiAddon/ImGuiLayer.h"
#include"Events/Event.h"
#include<vector>
namespace GU
{
    class Application
    {
    public:
        Application();
        virtual void Run();
        virtual ~Application();
        void OnEvent(Event& e);

        void PushLayer(Layer* layer);
        static Application* Get()
        {
            return s_Instance;
        }
        Window& GetWindow(){ return *m_window; }

        void Close(){ m_Running = false; }
    private:
        std::vector<Layer*> m_Layers;
        bool m_Running = true;
        std::unique_ptr<Window> m_window;
        static Application* s_Instance;
        ImGuiLayer* m_imGuiLayer;
        float m_LastFrameTime = 0.0f;
    };

    Application* CreateApplication();
}