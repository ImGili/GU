/*
 * @Author: ImGili
 * @Description: 
 */
#include"Core/Application.h"
#include"Core/Log.h"
#include"Core/Core.h"
#include"Core/Assert.h"
#include"Platform/OpenGL/OpenGLContext.h"
#include"Platform/OpenGL/OpenGLShader.h"
#include"Renderer/Shader.h"
GU::Application* GU::CreateApplication();
int main()
{
    GU::Log::Init();
    GU::Application* app = GU::CreateApplication();
    std::shared_ptr<GU::Shader> shader = GU::Shader::Create("aaa", "aaa", "aaa");
    GU_ERROR("hello word!");
    app->Run();
    return 0;
}
