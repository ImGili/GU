/*
 * @Author: ImGili
 * @Description: 
 */
#include"Renderer/Texture.h"
#include"Renderer/RenderAPI.h"
#include"Platform/OpenGL/OpenGLTexture.h"
using namespace GU;
std::shared_ptr<Texture> Texture::Create(uint32_t width, uint32_t height)
{
    switch (RenderAPI::GetAPI())
    {
    case RenderAPI::API::None:
        GU_ASSERT(false, "RenderAPI is None")
        break;
    case RenderAPI::API::OpenGL:
        return std::make_shared<OpenGLTexture>(width, height);
        break;
    default:
        break;
    }
    return nullptr;
}
std::shared_ptr<Texture> Texture::Create(const std::string& path)
{
    switch (RenderAPI::GetAPI())
    {
    case RenderAPI::API::None:
        GU_ASSERT(false, "RenderAPI is None")
        break;
    case RenderAPI::API::OpenGL:
        return std::make_shared<OpenGLTexture>(path);
        break;
    default:
        break;
    }
    return nullptr;
}