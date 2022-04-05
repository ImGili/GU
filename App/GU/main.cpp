#include"Core/EntryPoint.h"
#include"EditorLayer.h"
class GUApplication : public GU::Application
{
public:
    GUApplication(){
        PushLayer(new EditorLayer());
    }

    ~GUApplication()
    {}
};
GU::Application* GU::CreateApplication()
{
    return new GUApplication();
}