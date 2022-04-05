#include"Core/EntryPoint.h"
#include"ExampleLayer.h"
#include"EditorLayer.h"
#include"Example3DLayer.h"
class ExampleApplication : public GU::Application
{
public:
    ExampleApplication(){
        PushLayer(new EditorLayer());
    }

    ~ExampleApplication()
    {}
};
GU::Application* GU::CreateApplication()
{
    return new ExampleApplication();
}