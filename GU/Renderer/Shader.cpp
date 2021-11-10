#include"Shader.h"
#include"Renderer/RenderAPI.h"
#include"Platform/OpenGL/OpenGLShader.h"
#include"Core/Assert.h"
#include"Core/Log.h"
using namespace GU;
std::shared_ptr<Shader> Shader::Create(const char* name, const char* vertexPath, const char* fragmentPath, const char* geometryPath)
{
    switch (RenderAPI::GetAPI())
    {
    case RenderAPI::API::None:
        GU_ASSERT(false, "RenderAPI is None")
        break;
    case RenderAPI::API::OpenGL:
        GU_INFO("Create Shader: {0}", name);
        return std::make_shared<OpenGLShader>(name, vertexPath, fragmentPath, geometryPath);
        break;
    default:
        break;
    }
    return nullptr;
}
