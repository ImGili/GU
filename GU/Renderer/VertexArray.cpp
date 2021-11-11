/*
 * @Author: ImGili
 * @Description: 
 */
#include"Renderer/VertexArray.h"
#include"Renderer/RenderAPI.h"
#include"Core/Assert.h"
#include"Core/Log.h"
#include"Platform/OpenGL/OpenGLVertexArray.h"
using namespace GU;

std::shared_ptr<VertexArray> VertexArray::Create()
{
    switch (RenderAPI::GetAPI())
    {
    case RenderAPI::API::None:
        GU_ASSERT(false, "RenderAPI is None")
        break;
    case RenderAPI::API::OpenGL:
        return std::make_shared<OpenGLVertexArray>();
    default:
        break;
    }
    GU_ASSERT(false, "Renderer API can not create VertexArray!");
    return nullptr;
}