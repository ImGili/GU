/*
 * @Author: ImGili
 * @Description: 
 */
#include"GraphicsContext.h"
#include"RenderAPI.h"
#include"Core/Log.h"
#include"Core/Assert.h"
using namespace GU;
std::unique_ptr<GraphicsContext> GraphicsContext::Create(void* window)
{
    switch (RenderAPI::GetAPI())
    {
    case RenderAPI::API::None:
        GU_ASSERT(false, "RenderAPI is None");
        break;
    case RenderAPI::API::OpenGL:
        
        break;
    
    default:
        break;
    }
}