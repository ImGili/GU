/*
 * @Author: ImGili
 * @Description: 
 */
#include"GraphicsContext.h"
#include"RenderAPI.h"
#include"Core/Log.h"
using namespace GU;
std::unique_ptr<GraphicsContext> GraphicsContext::Create(void* window)
{
    switch (RenderAPI::GetAPI())
    {
    case RenderAPI::API::None:
        GU_ERROR("");
        GU_DEBUGBREAK();
        break;
    case RenderAPI::API::OpenGL:

        break;
    
    default:
        break;
    }
}