/*
 * @Author: ImGili
 * @Description: 
 */
#include"FrameBuffer.h"
#include"Platform/OpenGL/OpenGLFrameBuffer.h"
#include"Renderer/RenderAPI.h"
#include"Core/Log.h"
using namespace GU;
std::shared_ptr<FrameBuffer> FrameBuffer::Create(const FrameBufferSpecification& spec)
{
    switch (RenderAPI::GetAPI())
    {
    case RenderAPI::API::None:
        GU_ASSERT(false, "RenderAPI is None")
        break;
    case RenderAPI::API::OpenGL:
        return std::make_shared<OpenGLFrameBuffer>(spec);
        break;
    default:
        break;
    }
    return nullptr;
}
