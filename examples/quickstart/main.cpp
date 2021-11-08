#include"Core/EntryPoint.h"
#include"ExampleLayer.h"
class ExampleApplication : public GU::Application
{
public:
    ExampleApplication(){
        PushLayer(new ExampleLayer());
    }

    ~ExampleApplication()
    {}
};
GU::Application* GU::CreateApplication()
{
    return new ExampleApplication();
}