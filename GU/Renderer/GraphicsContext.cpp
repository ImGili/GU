/*
 * @Author: ImGili
 * @Description: 
 */
#include"GraphicsContext.h"
#include"RenderAPI.h"
#include"Core/Log.h"
#include"Core/Assert.h"
#include"Platform/OpenGL/OpenGLContext.h"
using namespace GU;
std::unique_ptr<GraphicsContext> GraphicsContext::Create(void* window)
{
    switch (RenderAPI::GetAPI())
    {
    case RenderAPI::API::None:
        GU_ASSERT(false, "RenderAPI is None");
        break;
    case RenderAPI::API::OpenGL:
        return std::make_unique<OpenGLContext>(std::forward<GLFWwindow*>(static_cast<GLFWwindow*>(window)));
        break;
    
    default:
        break;
    }
    return nullptr;
}