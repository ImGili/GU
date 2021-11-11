/*
 * @Author: ImGili
 * @Description: 
 */
#include"RenderAPI.h"
#include"Core/Log.h"
#include"Platform/OpenGL/OpenGLRenderAPI.h"
using namespace GU;

RenderAPI::API RenderAPI::s_API = RenderAPI::API::OpenGL;

RenderAPI::API RenderAPI::GetAPI()
{
    return s_API;
}
 
std::unique_ptr<RenderAPI> RenderAPI::Create()
{
    switch (s_API)
    {
    case API::None:
        GU_ERROR("RenderAPI is None");
        break;
    case API::OpenGL:
        return std::make_unique<OpenGLRenderAPI>();
        break;
    default:
        break;
    }
    GU_ERROR("API is not defined!");
}