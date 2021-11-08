/*
 * @Author: ImGili
 * @Description: 
 */
#include"Application.h"
#include"Log.h"
GU::Application* GU::CreateApplication();
int main()
{
    GU::Log::Init();
    GU::Application* app = GU::CreateApplication();

    GU_WARN("hello word!");
    app->Run();
    return 0;
}
