/*
 * @Author: ImGili
 * @Description: 
 */
#include"Renderer/Buffer.h"
#include"Renderer/RenderAPI.h"
#include"Platform/OpenGL/OpenGLBuffer.h"
#include"Core/Log.h"
#include"Core/Assert.h"
using namespace GU;

std::shared_ptr<VertexBuffer> VertexBuffer::Create(float* data, uint32_t size)
{
    switch (RenderAPI::GetAPI())
    {
    case RenderAPI::API::None:
        GU_ASSERT(false, "RenderAPI is None")
        break;
    case RenderAPI::API::OpenGL:
        return std::make_shared<OpenGLVertexBuffer>(data, size);
        break;
    default:
        break;
    }
    return nullptr;
}
std::shared_ptr<VertexBuffer> VertexBuffer::Create(uint32_t size)
{
    switch (RenderAPI::GetAPI())
    {
    case RenderAPI::API::None:
        GU_ASSERT(false, "RenderAPI is None")
        break;
    case RenderAPI::API::OpenGL:
        return std::make_shared<OpenGLVertexBuffer>(size);
        break;
    default:
        break;
    }
    return nullptr;
}

std::shared_ptr<IndexBuffer> IndexBuffer::Create(const uint32_t* indics, uint32_t count)
{
    switch (RenderAPI::GetAPI())
    {
    case RenderAPI::API::None:
        GU_ASSERT(false, "RenderAPI is None")
        break;
    case RenderAPI::API::OpenGL:
        return std::make_shared<OpenGLIndexBuffer>(indics, count);
        break;
    default:
        break;
    }
    return nullptr;
}